#include "reportinteractive.hpp"
#include "decompress.hpp"

const QString ReportInteractive::Terminal::deleteLine = QString::fromUtf8("\r\e[K");  ///< 현재 라인 지우기

const QString ReportInteractive::Terminal::reset = QString::fromUtf8("\e[39;49;00m"); ///< 터미널 설정을 초기화

const QString ReportInteractive::Terminal::red = QString::fromUtf8("\e[31;01m"); ///< 빨강색

const QString ReportInteractive::Terminal::yellow = QString::fromUtf8("\e[33;01m"); ///< 노란색

const QString ReportInteractive::Terminal::green = QString::fromUtf8("\e[32;01m"); ///< 초록색

/** 소멸자.
  */
ReportInteractive::~ReportInteractive(){}

/** 변경된 이름을 설정합니다.
  */
void ReportInteractive::setNewName(
        QString newName  ///< 새로운 이름
        )
{
    stdout << Terminal::green << trUtf8("\t\t중복 회피를 위해 파일명을 `%1'로 바꾸어 저장합니다.").arg(newName) << Terminal::reset << endl
           << flush;
}

void ReportInteractive::setOpenFileError(
        QString fileName ///< 압축 파일명
        )
{
    QString m = trUtf8("`%1' 파일을 여는데 문제가 생겼습니다. 작업을 건너 뜁니다.").arg(fileName);
    setWarning(m);
}

/** 현재 총 압축 해제율을 설정합니다.
  */
void ReportInteractive::setTotalPercent(
        float percent    ///< 압축 해제율
        )
{
    //압축 해제율애 대한 정보를 표준출력으로 출력한다.
    stdout << trUtf8("\t\t전체 진행율은 %1%%입니다.").arg(percent) << endl
           << flush;
}

/** 현재 부분 압축 해제율을 설정합니다.
  */
void ReportInteractive::reportCurrentPercent(
        float percent    ///< 압축 해제율
        )
{
    //압축 해제율애 대한 정보를 표준출력으로 출력한다.
    stdout << Terminal::deleteLine << trUtf8("\t\t현재 진행율은 %1%%입니다.").arg(percent)
           << flush;
}

/** 부분 압축 해제가 완료되었음을 설정한다.
  */
void ReportInteractive::setPartEnd()
{
    //현재 줄을 삭제시켜, 다음 출력이 빈 줄의 시작점에서 시작될수 있도록 하게 한다.
    stdout << Terminal::deleteLine
           << flush;
}

/** 압축 해제가 끝나면 호출되는 메소드.
  */
void ReportInteractive::setEndFile()
{
    // 줄바꿈 문자를 삽입하여, 다음 압축 파일과 간격을 만듭니다.
    stdout << endl
           << flush;
}

/** 객체를 생성합니다.
  */
ReportInteractive::ReportInteractive(
        QObject *parent
        ) :
    QObject(parent),
    stdout(::stdout),
    stdin(::stdin),
    stderr(::stderr)
{
    //ReportInteractive 객체를 생성합니다.
}

/** 압축 해제 중 오류를 설정한다.
  */
void ReportInteractive::setDecompressError(
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

/** 사용자로 부터 암호를 입력받습니다.
  @return 입력받은 암호
  */
QString ReportInteractive::getPassword()
{
    stdout << trUtf8("\t\t암호는? ") << flush;
    QString password = stdin.readLine();
    return password;
}

/** 암호가 걸린 파일을 건너뜀을 알립니다.
  */
void ReportInteractive::reportSkipLockFile(
        QString fileName ///< 파일명
        )
{
    QString m = trUtf8("`%1'에 포함된 `%2'의 암호 설정을 건너뜁니다.").arg(currentFileName, fileName);
    setWarning(m);
}

/** 경고 메시지를 등록합니다.
  */
void ReportInteractive::setWarning(
        QString mesg  ///< 메시지
        )
{
    //모든 시작은 줄의 처음 부터이므로, 현재 줄에 진행 상태가 표시되었다면 이 줄을 깨끗이 비울수 있도록 Terminal::deleteLine를 사용한다.
    stderr << Terminal::deleteLine << Terminal::yellow << mesg << Terminal::reset << endl
           << flush;
}

/** 경고 보다 한 단계 높은 주의를 요하는 메시지를 등록합니다.
  */
void ReportInteractive::setCritical(
        QString mesg ///< 메시지
        )
{
    //모든 시작은 줄의 처음 부터이므로, 현재 줄에 진행 상태가 표시되었다면 이 줄을 깨끗이 비울수 있도록 Terminal::deleteLine를 사용한다.
    stderr << Terminal::deleteLine << Terminal::red << mesg << Terminal::reset << endl
           << flush;
}

/** 전체 저장 경로를 설정합니다.
  */
void ReportInteractive::setExtractPath(
        QString path    ///< 저장 할 경로
        )
{
    stdout << trUtf8("전체 저장 위치 : %1").arg(path) << endl
           << endl
           << flush;
}

/** 부분 저장 경로를 설정합니다.
  */
void ReportInteractive::setSeperatedExtractPath(
        QString path    ///< 저장 할 경로
        )
{
    stdout << trUtf8("저장 위치 : %1").arg(path) << endl
           << flush;
}

/** 압축 해제중인 파일의 정보를 설정합니다.
  */
void ReportInteractive::customSetStartFile(
        int index,          ///< 압축 해제 중인 파일의 인덱스
        QString fileName    ///< 압축 해제 중인 파일 명
        )
{
    stdout << QString::fromUtf8("[%1/%2] %3 :").arg(index + 1).arg(getTotalArchiveCount()).arg(fileName) << endl
           << flush;
}

/** 압축 해제 중인 파일에서 압축 해제되고 있는 파일의 이름을 설정합니다.
  */
void ReportInteractive::customSetExtractFileStart(
        QString fileName   ///< 압축 해제 중인 파일 이름
        )
{
    stdout << QString::fromUtf8("\t%1").arg(fileName) << endl
           << flush;
}
