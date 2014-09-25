#include "decompress.hpp"
#include "reportinteractivenoterminal.hpp"

/** 소멸자.
  */
ReportInteractiveNoTerminal::~ReportInteractiveNoTerminal(){}

/** 변경된 이름을 설정합니다.
  */
void ReportInteractiveNoTerminal::setNewName(
        QString newName  ///< 새로운 이름
        )
{
    stdout << trUtf8("\t\t중복 회피를 위해 파일명을 `%1'로 바꾸어 저장합니다.").arg(newName) << endl
           << flush;
}

/** 분할 저장 폴더 생성 실패에 대한 오류를 설정한다.
  */
void ReportInteractiveNoTerminal::setMakeFailSeperatedFolder(
        const QString &archiveFilePath, ///< 압축파일경로
        const QString &defaultSavePath  ///< 기본 저장 위치
        )
{
    QString errorMesg = trUtf8("압축 파일 `%1'에 대한 분할된 폴더를 생성하는데 실패했습니다. 기본 위치(%2)에 저장합니다.").arg(archiveFilePath, defaultSavePath);
    setWarning(errorMesg);
}

/** 암호가 걸린 파일을 건너뜀을 알립니다.
  */
void ReportInteractiveNoTerminal::reportSkipLockFile(
        QString fileName ///< 파일명
        )
{
    QString m = trUtf8("`%1'에 포함된 `%2'의 암호 설정을 건너뜁니다.").arg(currentFileName, fileName);
    setWarning(m);
}

void ReportInteractiveNoTerminal::setOpenFileError(
        QString fileName ///< 압축 파일명
        )
{
    QString m = trUtf8("`%1' 파일을 여는데 문제가 생겼습니다. 작업을 건너 뜁니다.").arg(fileName);
    setWarning(m);
}

/** 압축 해제 중 오류를 설정한다.
  */
void ReportInteractiveNoTerminal::setDecompressError(
        QString archiveFilePath,
        QString partFilePath,
        QString errorMessage
        )
{
    //오류 메시지를 설정
    QString s;

    if ( partFilePath.isNull() ) {
        s = trUtf8("`%1'파일을 압축해제 하던 중 오류가 발생했습니다. %3").arg(archiveFilePath, errorMessage);
    }
    else {
        s = trUtf8("`%1'파일의 `%2'파일을 압축해제 하던 중 오류가 발생했습니다. %3").arg(archiveFilePath, partFilePath, errorMessage);
    }

    setCritical(s);
}

/** 현재 총 압축 해제율을 설정합니다.
  */
void ReportInteractiveNoTerminal::setTotalPercent(float){}

/** 현재 부분 압축 해제율을 설정합니다.
  */
void ReportInteractiveNoTerminal::reportCurrentPercent(float){}

/** 부분 압축 해제가 완료되었음을 설정한다.
  */
void ReportInteractiveNoTerminal::setPartEnd(){}

/** 압축 해제가 끝나면 호출되는 메소드.
  */
void ReportInteractiveNoTerminal::setEndFile()
{
    // 줄바꿈 문자를 삽입하여, 다음 압축 파일과 간격을 만듭니다.
    stdout << endl
           << flush;
}

/** 객체를 생성합니다.
  */
ReportInteractiveNoTerminal::ReportInteractiveNoTerminal(
        QObject *parent
        ) :
    QObject(parent),
    stdout(::stdout),
    stdin(::stdin),
    stderr(::stderr)
{
    //ReportInteractiveNoTerminal 객체를 생성합니다.
}

/** 빈 암호를 반환합니다.
  @return 빈 QString 객체.
  */
QString ReportInteractiveNoTerminal::getPassword()
{
    return QString::null;
}

/** 경고 메시지를 등록합니다.
  */
void ReportInteractiveNoTerminal::setWarning(
        QString mesg  ///< 메시지
        )
{
    stderr << mesg << endl
           << flush;
}

/** 경고 보다 한 단계 높은 주의를 요하는 메시지를 등록합니다.
  */
void ReportInteractiveNoTerminal::setCritical(
        QString mesg ///< 메시지
        )
{
    stderr << mesg << endl
           << flush;
}

/** 전체 저장 경로를 설정합니다.
  */
void ReportInteractiveNoTerminal::setExtractPath(
        QString path    ///< 저장 할 경로
        )
{
    stdout << trUtf8("전체 저장 위치 : %1").arg(path) << endl
           << endl
           << flush;
}

/** 부분 저장 경로를 설정합니다.
  */
void ReportInteractiveNoTerminal::setSeperatedExtractPath(
        QString path    ///< 저장 할 경로
        )
{
    stdout << trUtf8("저장 위치 : %1").arg(path) << endl
           << flush;
}

/** 압축 해제중인 파일의 정보를 설정합니다.
  */
void ReportInteractiveNoTerminal::customSetStartFile(
        int index,          ///< 압축 해제 중인 파일의 인덱스
        QString fileName    ///< 압축 해제 중인 파일 명
        )
{
    stdout << QString::fromUtf8("[%1/%2] %3 :").arg(index + 1).arg(getTotalArchiveCount()).arg(fileName) << endl
           << flush;
}

/** 압축 해제 중인 파일에서 압축 해제되고 있는 파일의 이름을 설정합니다.
  */
void ReportInteractiveNoTerminal::customSetExtractFileStart(
        QString fileName   ///< 압축 해제 중인 파일 이름
        )
{
    stdout << QString::fromUtf8("\t%1").arg(fileName) << endl
           << flush;
}
