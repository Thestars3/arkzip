#include "report.hpp"

/** 보고 인스턴스를 설정합니다.
  @warning 설정된 객체의 범위는 프로그램 전체여야 하며, 설정된 객체에 대한 할당 해제는 내부적으로 이뤄집니다.
  */
void Report::setInstance(
        Report *instance ///< 저장할 객체의 주소. 반드시 동적 할당된 객체의 주소를 넘겨줘야 합니다.
        )
{
    //이전에 할당된 객체가 존재한다면 할당 해제한다.
    if ( singleton != nullptr ){
        delete singleton;
        singleton = nullptr;
    }

    //새로운 싱글톤을 설정한다.
    singleton = instance;
}

void Report::setSeperatedExtractPath(QString){}

void Report::reportSkipLockFile(QString){}

Report *Report::singleton = new Report(); ///< 싱글톤

/** 전역 객체를 얻습니다.
  @return 전역 객체
  */
Report* Report::getInstance()
{
    return singleton;
}

/** 전체 압축 파일의 수를 설정합니다.
  */
void Report::setTotalArchiveCount(
        int totalArchiveCount ///< 전체 압축 파일의 수
        )
{
    totalArchiveCount_ = totalArchiveCount;
}

/** 전체 압축 파일의 수를 반환합니다.
  @return 전체 압축 파일의 수
  */
int Report::getTotalArchiveCount()
{
    return totalArchiveCount_;
}

/** 생성자.
  */
Report::Report()
{
    //'압축 파일에서 압축 해제되고 있는 파일'의 압축 해제 진행율 표시에 사용되는 타이머를 설정
    {
        setPartTimerInterval(1000);   //1초 간격으로 작동하게 한다.
        partTimer.setSingleShot(true);
    }

    //전체 압축 해제율 표시 타이머 설정
    {
        setTotalTimerInterval(3000); //3초 간격으로 작동하게 한다.
        totalTimer.setSingleShot(true);
    }
}

/** 전체 타이머의 작동 간격을 설정합니다.
  */
void Report::setTotalTimerInterval(
        int ms ///< 밀리세컨드
        )
{
    totalTimer.setInterval(ms);
}

/** 부분 타이머의 작동 간격을 설정합니다.
  */
void Report::setPartTimerInterval(
        int ms ///< 밀리세컨드
        )
{
    partTimer.setInterval(ms);
}

/** 소멸자.
  */
Report::~Report(){}

/** 부분 진행율을 보고합니다.
  */
void Report::reportCurrentPercent(float){}

/** 전체 진행율을 보고합니다.
  */
void Report::reportTotalPercent(float){}

/** 압축 파일의 전체 압축 해제율을 설정한다.
  */
void Report::setTotalPercent(
        float percent   ///< 전체 진행율
        )
{
    //타이머가 꺼져있다면
    if ( ! totalTimer.isActive() ){
        // 전체 진행 정보를 보고합니다.
        reportTotalPercent(percent);

        //타이머를 다시 시작시킵니다.
        totalTimer.start();
    }
}

/** 압축 파일에서 압축 해제 중인 파일의 압축 해제율을 설정한다.
  */
void Report::setCurrentPercent(
        float percent   ///< 부분 진행율
        )
{
    //타이머가 꺼져있다면
    if ( ! partTimer.isActive() ){
        // 부분 진행 정보를 보고합니다.
        reportCurrentPercent(percent);

        //타이머를 다시 시작시킵니다.
        partTimer.start();
    }
}

/** 압축 해제를 시작을 설정한다. 압축 파일의 정보를 설정한다.
  */
void Report::setStartFile(
        int index,         ///< 인덱스
        QString fileName   ///< 파일명
        )
{
    totalTimer.start();
    currentFileName = fileName;
    customSetStartFile(index, fileName);
}

void Report::customSetStartFile(int, QString){}

/** 압축 파일에서 압축 해제 중인 파일의 정보를 설정한다.
  */
void Report::setExtractFileStart(
        QString fileName   ///< 파일명
        )
{
    partTimer.start();
    customSetExtractFileStart(fileName);
}

void Report::customSetExtractFileStart(QString){}

/** 부분 압축 해제가 완료되었음을 설정한다.
  */
void Report::setPartEnd(){}

/** 전체 저장 경로를 설정한다.
  */
void Report::setExtractPath(QString){}

/** 오류 메시지를 설정한다.
  */
void Report::setWarning(QString){}

/** 새로운 이름을 설정한다.
  */
void Report::setNewName(QString){}

/** 암호를 입력받는다.
  @return 아무값도 없는 QStirng 객체.
  */
QString Report::getPassword()
{
    return QString::null;
}

/** 압축 파일이 압축 해제 완료 되었음을 설정한다.
  */
void Report::setEndFile(){}

/** 치명적인 오류를 설정합니다.
  */
void Report::setCritical(QString){}
