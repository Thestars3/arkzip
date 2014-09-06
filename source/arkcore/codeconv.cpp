#include "ArkLibrary.hpp"
#include <unicode/ucnv.h>
#include "codeconv.hpp"

CodeConv::CodeConv()
{
    convert =
            [this] (
                const SArkFileItem *pFileItem
                ) -> QString
        {
            return QString::fromStdWString(pFileItem->fileNameW);
        };
}

CodeConv* CodeConv::getInstance()
{
    return singleton;
}

CodeConv *CodeConv::singleton = new CodeConv();

/** 코드 페이지를 설정합니다.\n
  설정 가능한 코드페이지는 <a href="http://demo.icu-project.org/icu-bin/convexp">Converter Explorer</a>를 참고하십시오.
  @return 성공시 true, 실패시 false를 반환합니다.
  */
bool CodeConv::setCodepage(
        const QString &codepageName ///< 코드페이지명
        )
{
    //변환기 초기화
    UErrorCode status = U_ZERO_ERROR;
    conv = ucnv_open(codepageName.toUtf8().constData(), &status);
    if ( U_FAILURE(status) ) {
        return false;
    }

    //변환 명령 설정
    convert =
            [this] (
                const SArkFileItem *pFileItem
                ) -> QString
        {
            QString filename;

            if ( pFileItem->isUnicodeFileName == TRUE ) {
                filename = QString::fromStdWString(pFileItem->fileNameW);
            }
            else {
                const char *src = pFileItem->fileName;
                const char *srcEnd = src + qstrlen(src);
                UErrorCode status = U_ZERO_ERROR;

                UChar32 c;
                while ( src < srcEnd ) {
                    c = ucnv_getNextUChar(conv, &src, srcEnd, &status);
                    filename += QChar((uint)c);
                }
            }

            return filename;
        };

    return true;
}

/** 파일명을 QString으로 반환합니다.
  @return 파일명을 담은 QString
  */
QString CodeConv::toQString(
        const SArkFileItem *pFileItem ///< 파일 정보 구조체
        )
{
    return convert(pFileItem);
}
