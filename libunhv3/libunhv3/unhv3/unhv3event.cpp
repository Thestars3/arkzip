#include <QFileInfo>
#include "EventInterface.hpp"
#include "unhv3event.hpp"

/** 생성자.
  */
Unhv3Event::Unhv3Event()
{
    event_ = nullptr;
}

/** 이벤트 객체를 설정합니다. \n
  만약, nullptr을 넘겨주면, 이벤트 처리가 중단됩니다.
  */
void Unhv3Event::setEvent(
        IArkEvent *event ///< 이벤트 객체 포인터
        )
{
    event_ = event;
}

/** 압축 파일의 시작을 알립니다.
  */
void Unhv3Event::setOpen()
{
    if ( event_ == nullptr ) {
        return;
    }

    BOOL32 bStop;
    event_->OnOpening(nullptr, 0, bStop);
}

/** 압축에 포함된 파일의 압축해제 시작을 알립니다.
  */
void Unhv3Event::setStartFile(
        const QString &filePath
        )
{
    if ( event_ == nullptr ) {
        return;
    }

    BOOL32 b;
    SArkFileItem fileItem;

    fileItem.isUnicodeFileName = true;
    fileItem.fileNameW = const_cast<WCHAR*>(filePath.toStdWString().c_str());

    event_->OnStartFile(&fileItem, b, b, 0);
}

/** 중복 파일이 발견되었을 경우 이 메소드를 사용하여 중복 회피명을 얻습니다.
  @return 중복 회피 경로
  */
QString Unhv3Event::convertDuplicatedName(
        const QString &filePath ///< 파일명이 포함된 경로
        )
{
    if ( event_ == nullptr ) {
        return filePath;
    }

    LPCWSTR szLocalPathName = QFileInfo(filePath).absolutePath().toStdWString().c_str();
    ARK_OVERWRITE_MODE overwrite;
    WCHAR pathName2Rename[ARK_MAX_PATH];

    event_->OnAskOverwrite(nullptr, szLocalPathName, overwrite, pathName2Rename);

    return QString::fromWCharArray(pathName2Rename);
}

/** 특정 파일에 대한 오류를 설정합니다.
  */
void Unhv3Event::setError(
        const QString &filePathName,
        const Unhv3Status &status
        )
{
    if ( event_ == nullptr ) {
        return;
    }

    SArkFileItem fileItem;
    ARKERR nErr = ArkerrConverter::ConvertUnhv3Status(status);
    BOOL32 b;

    fileItem.isUnicodeFileName = true;
    fileItem.fileNameW = const_cast<WCHAR*>(filePathName.toStdWString().c_str());

    event_->OnError(nErr, &fileItem, 0, b);
}

/** 푸는 중인 파일의 진행율을 알립니다.
  */
void Unhv3Event::setProgress(
        float progress
        )
{
    if ( event_ == nullptr ) {
        return;
    }

    BOOL32 b;
    SArkProgressInfo progressInfo;

    progressInfo.fCurPercent = progress;

    event_->OnProgressFile(&progressInfo, b, b);
}

/** 압축 파일의 끝임을 알립니다.
  */
void Unhv3Event::setComplete()
{
    if ( event_ == nullptr ) {
        return;
    }

    SArkProgressInfo progressInfo;

    progressInfo.fTotPercent = 100;

    event_->OnCompleteFile(&progressInfo, ARKERR_NOERR);
}
