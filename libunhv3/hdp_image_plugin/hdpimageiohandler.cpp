#include <QImage>
#include <cstring>
#include <JXRGlue.h>
#include "hdpimageiohandler.hpp"

#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static ERR PKImageEncode_WritePixels_RAW(PKImageEncode *pIE, U32 cLine, U8 *pbPixel, U32 cbStride);

bool HdpImageIOHandler::canRead() const
{
    if ( ! device() ) {
        qWarning("HdpImageIOHandler::canRead() 불러올 장치를 지정하지 않았습니다.");
        return false;
    }

    // HDP의 magic numbe는 ASCII로 `II.'이고, 위치한 offset은 0이다.
    const qint64 oldPos = device()->pos();

    char head[3];
    qint64 readBytes = device()->read(head, sizeof(head));
    const bool readOk = ( readBytes == sizeof(head) );

    if ( device()->isSequential() ) {
        while (readBytes > 0) {
            device()->ungetChar(head[ readBytes-- - 1 ]);
        }
    }
    else {
        device()->seek(oldPos);
    }

    if ( ! readOk ) {
        return false;
    }

    return( head[0] == 'I' && head[1] == 'I' && head[2] == '.' );
}

bool HdpImageIOHandler::read(
        QImage *outImage
        )
{
    ERR err = WMP_errSuccess;

    PKImageDecode *pDecoder = nullptr;
    PKFactory *pFactory = nullptr;
    PKCodecFactory *pCodecFactory = nullptr;
    WMPStream *pEncodeStream = nullptr; // 인코드 스트림
    PKImageEncode *pEncoder = nullptr; // 인코더
    PKFormatConverter *pConverter = nullptr; // 컨버터
    PKPixelFormatGUID guidPixFormat;
    size_t bufferSize;
    U8 *buffer;
    PKRect rect = {0, 0, 0, 0}; // 크기

    Call(PKCreateFactory(&pFactory, PK_SDK_VERSION));
    Call(PKCreateCodecFactory(&pCodecFactory, WMP_SDK_VERSION));
    Call(PKCodecFactory_CreateDecoderFromMemory(&pDecoder));

    pDecoder->WMP.bIgnoreOverlap = FALSE;

    // < -- Validate thumbnail decode parameters -- >
    pDecoder->WMP.wmiI.cThumbnailWidth = pDecoder->WMP.wmiI.cWidth;
    pDecoder->WMP.wmiI.cThumbnailHeight = pDecoder->WMP.wmiI.cHeight;
    pDecoder->WMP.wmiI.bSkipFlexbits = FALSE;

    // < -- 디코딩 영역 지정 -- >
    pDecoder->WMP.wmiI.cROILeftX = 0; // 전체 디코딩
    pDecoder->WMP.wmiI.cROITopY = 0;
    pDecoder->WMP.wmiI.cROIWidth = pDecoder->WMP.wmiI.cThumbnailWidth;
    pDecoder->WMP.wmiI.cROIHeight = pDecoder->WMP.wmiI.cThumbnailHeight;

    // < -- 이미지 방향 설정 -- >
    pDecoder->WMP.wmiI.oOrientation = O_NONE; // 원본 그대로 유지

    // < -- 이미지 전처리 설정 -- >
    pDecoder->WMP.wmiI.cPostProcStrength = 0; // 전처리 없음

    // < -- 작업 현황 보고 설정 -- >
    pDecoder->WMP.wmiSCP.bVerbose = FALSE; // 보고 안함

    // < -- 알파값 유무에 따른 포멧 선택 -- >
    if ( pDecoder->WMP.bHasAlpha ) {
        guidPixFormat = GUID_PKPixelFormat32bppRGBA;
        bufferSize = pDecoder->uWidth * pDecoder->uHeight * 4;
    }
    else {
        guidPixFormat = GUID_PKPixelFormat24bppRGB;
        bufferSize = ( pDecoder->uWidth * 3 + pDecoder->uWidth * 3 % 4 ) * pDecoder->uHeight;
    }

    // < -- 컨버터 초기화 -- >
    Call(pCodecFactory->CreateFormatConverter(&pConverter));
    Call(pConverter->Initialize(pConverter, pDecoder, nullptr, guidPixFormat)); // 널 포인터를 인자로 주어 확장자에 따른 픽셀 포멧 지정을 막음.

    // < -- 인코더 준비 -- >
    buffer = reinterpret_cast<U8*>(malloc( bufferSize * sizeof(U8) ));
    Call(pFactory->CreateStreamFromMemory(&pEncodeStream, buffer, bufferSize));
    Call(PKImageEncode_Create(&pEncoder));
    pEncoder->WritePixels = PKImageEncode_WritePixels_RAW;
    pEncoder->Initialize(pEncoder, pEncodeStream, nullptr, 0);

    // < -- 출력 화소 포멧 설정 -- >
    Call(pEncoder->SetPixelFormat(pEncoder, guidPixFormat));
    pEncoder->WMP.wmiSCP.bBlackWhite = pDecoder->WMP.wmiSCP.bBlackWhite;

    // < -- 출력 이미지 크기 설정 -- >
    rect.Width = static_cast<I32>(pDecoder->WMP.wmiI.cROIWidth);
    rect.Height = static_cast<I32>(pDecoder->WMP.wmiI.cROIHeight);
    Call(pEncoder->SetSize(pEncoder, rect.Width, rect.Height));

    // < -- 출력 해상도 설정 -- >
    {
        Float rX = 0.0, rY = 0.0; // 해상도
        Call(pDecoder->GetResolution(pDecoder, &rX, &rY)); // 디코더의 해상도를 가져옵니다.
        Call(pEncoder->SetResolution(pEncoder, rX, rY)); // 인코더의 해상도를 디코더의 해상도로 설정합니다.
    }

    // < -- 변환된 내용을 기록 -- >
    pEncoder->WriteSource = PKImageEncode_Transcode;
    Call(pEncoder->WriteSource(pEncoder, pConverter, &rect));
    writeImage(pEncoder, outImage);

    // < -- 인코더 할당 해제 -- >
    pEncoder->Release(&pEncoder);

    // < -- 디코더 할당 해제 -- >
    pDecoder->Release(&pDecoder);

Cleanup:
    if ( Failed(err) ) {
        return false;
    }

    return true;
}

void HdpImageIOHandler::writeImage(
        PKImageEncode *pEncoder,
        QImage *outImage
        )
{
    QImage::Format format;
    size_t bufferSize = pEncoder->pStream->state.buf.cbBuf;
    uchar *buffer = pEncoder->pStream->state.buf.pbBuf;
    uint line;

    // < --  알파값 유무에 따른 설정 -- >
    if ( pEncoder->WMP.bHasAlpha ) {
        format = QImage::Format_ARGB32;
        convertRgbaToArgb(buffer, bufferSize);
        line = pEncoder->uWidth * 4;
    }
    else {
        format = QImage::Format_RGB888;
        line = pEncoder->uWidth * 3;
    }

    // < -- 이미지 초기화 -- >
    *outImage = QImage(pEncoder->uWidth, pEncoder->uHeight, format);

    // < -- 해상도 설정 -- >
    //JXR 라이브러리에서 사용하는 해상도 단위는 인치. QT에서 쓰는건 미터단위.
    outImage->setDotsPerMeterX(inchConvertToMeter(pEncoder->fResX));
    outImage->setDotsPerMeterY(inchConvertToMeter(pEncoder->fResY));

    // < -- 데이터 복사 -- >
    {
        uint stride = outImage->bytesPerLine();
        uchar *dest = outImage->bits();
        uchar *src = buffer;
        for(uint y = 0; y < pEncoder->uHeight; y++){
            std::memcpy(dest, src, line);
            dest += stride;
            src += line;
        }
    }
}

ERR HdpImageIOHandler::PKCodecFactory_CreateDecoderFromMemory(
        PKImageDecode **ppDecoder ///< PKImageDecode 이중 포인터
        )
{
    ERR err = WMP_errSuccess;

    const PKIID *pIID = nullptr;

    struct WMPStream *pStream = nullptr;
    PKImageDecode *pDecoder = nullptr;
    QByteArray source(device()->readAll());
    U8 *src;
    uint ps = static_cast<uint>(source.size());

    // get decode PKIID
    Call(GetImageDecodeIID(".hdp", &pIID));

    // create stream
    src = (U8*)malloc(source.size());
    src = (U8*)memcpy(src, source.data(), ps);
    Call(CreateWS_Memory(&pStream, src, static_cast<size_t>(source.size())));

    // Create decoder
    Call(PKCodecFactory_CreateCodec(pIID, reinterpret_cast<void**>(ppDecoder)));
    pDecoder = *ppDecoder;

    // attach stream to decoder
    Call(pDecoder->Initialize(pDecoder, pStream)); // 이 부분에서 이미지 데이터의 내용을 분석한다.
    pDecoder->fStreamOwner = !0;

Cleanup:
    return err;
}

/** RGBA 순서로된 바이트 배열을 ARGB 순서로 재배열한다.
  */
void HdpImageIOHandler::convertRgbaToArgb(
        uchar *p,   ///< 재배열 할 데이터 포인터
        uint size   ///< 재배열 할 데이터 사이즈
        )
{
    quint8 r, g, b, a;
    uint i = 0;
    while( i < size ) {
        r = p[0];
        g = p[1];
        b = p[2];
        a = p[3];

        *p++ = a;
        *p++ = r;
        *p++ = g;
        *p++ = b;

        i += 4;
    }
}

ERR PKImageEncode_WritePixels_RAW(
        PKImageEncode *pIE, ///< PKImageEncode
        U32 cLine,          ///< 픽셀 데이터의 한 열의 높이
        U8 *pbPixel,        ///< 픽셀 데이터
        U32 cbStride        ///< 픽셀 데이터의 한 행의 폭
        )
{
    ERR err = WMP_errSuccess;

    struct WMPStream* pS = pIE->pStream;
    size_t cbLineM = 0;

    pIE->fHeaderDone = !FALSE;

    // calculate line size in memory and in stream
    cbLineM = pIE->cbPixel * pIE->uWidth;

    FailIf(cbStride < cbLineM, WMP_errInvalidParameter);

    pS->Write(pS, pbPixel, pS->state.buf.cbBuf);

    pIE->idxCurrentLine += cLine;

Cleanup:
    return err;
}
