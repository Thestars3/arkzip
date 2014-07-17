#include "reportgui.hpp"
#include "decompress.hpp"
#include "pause.hpp"

ReportGui::~ReportGui(){}

/** 변경된 이름을 설정합니다.
  */
void ReportGui::setNewName(
        QString newName  ///< 새로운 이름
        )
{
    QString s = trUtf8("<font color=\"green\"><b>%3</b>에 포함된 <b>%1</b>이 중복되어 새로운 이름 <b>%2</b>을 지정합니다.</font>").arg(decompressFileName, newName, currentFileName);
    emit appendMessage(s);
}

void ReportGui::setPartEnd()
{
    emit changeCurrentPercent(1000);
}

void ReportGui::setCritical(
        QString message
        )
{
    QString m = trUtf8("<font color=\"red\">%1</font>").arg(message);
    emit appendMessage(m);
}

/** 압축 해제가 끝남.
  */
void ReportGui::setEndFile()
{
    emit changeTotalPercent(1000);
}

/** 현재 총 압축 해제율을 설정합니다.
  */
void ReportGui::reportTotalPercent(
        float percent    ///< 압축 해제율
        )
{
    int p = percent * 10;
    emit changeTotalPercent(p);
}

/** 현재 부분 압축 해제율을 설정합니다.
  */
void ReportGui::reportCurrentPercent(
        float percent    ///< 압축 해제율
        )
{
    int p = percent * 10;
    emit changeCurrentPercent(p);
}

/** 객체를 생성합니다.
  */
ReportGui::ReportGui(
        QObject *parent
        ) :
    QObject(parent)
{
    //전체 진행을 표시하는 간격을 1초로 수정.
    setTotalTimerInterval(1000);

    //전체 진행을 표시하는 간격을 0.5초로 수정
    setPartTimerInterval(500);
}

/** 사용자로 부터 암호를 입력받습니다.
  @return 입력받은 암호
  */
QString ReportGui::getPassword()
{
    //정지 설정
    Pause::getInstance()->pause();

    //암호 입력 받기.
    QString p;
    emit getPasswordSignal(&p);

    //정지 지점 설정
    Pause::getInstance()->setPausePoint();

    //입력값 반환
    return p;
}

/** 경고 메시지를 등록합니다.
  */
void ReportGui::setWarning(
        QString mesg  ///< 메시지
        )
{
    QString s = trUtf8("<font color=\"#FFD901\">%1</font>").arg(mesg);
    emit appendMessage(s);
}

/** 전체 저장 경로를 설정합니다.
  */
void ReportGui::setExtractPath(
        QString path ///< 경로
        )
{
    QString s = trUtf8("전체 저장 경로는 <b><a href=\"%1\">%1</a></b>입니다.").arg(path);
    emit appendMessage(s);
}

/** 분할된 저장 경로를 설정합니다.
  */
void ReportGui::setSeperatedExtractPath(
        QString path ///< 경로
        )
{
    QString s = trUtf8("<b>%1</b>의 저장 경로는 <b><a href=\"%2\">%2</a></b>입니다.").arg(currentFileName, path);
    emit appendMessage(s);
}

/** 압축 해제중인 파일의 정보를 설정합니다.
  */
void ReportGui::customSetStartFile(
        int index,          ///< 압축 해제 중인 파일의 인덱스
        QString fileName    ///< 압축 해제 중인 파일 명
        )
{
    currentFileName = fileName;
    QString s = QString::fromUtf8("[%1/%2] %3").arg(index + 1).arg( getTotalArchiveCount() ).arg(fileName);
    emit setArchiveInfoSignal(s);
}

/** 압축 해제 중인 파일에서 압축 해제되고 있는 파일의 이름을 설정합니다.
  */
void ReportGui::customSetExtractFileStart(
        QString fileName   ///< 압축 해제 중인 파일 이름
        )
{
    decompressFileName = fileName;
    emit setExtractFileNameSignal(fileName);
}
