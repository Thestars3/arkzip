#include "pause.hpp"

/** 객체를 초기화합니다.
  */
Pause::Pause(
        QObject *parent    ///< 부모 객체
        ) :
    QObject(parent),
    pauseStatus(false)
{
}

/** 일시정지 상태를 알아냅니다.
  @return true : 일시정지 됨.\n false : 일시정지 아님.
  */
bool Pause::isPaused()
{
    return pauseStatus;
}

Pause *Pause::singleton = new Pause(); ///< 싱글톤 객체

/** 전역 객체를 얻습니다.
  @return 전역 객체
  */
Pause* Pause::getInstance()
{
    return singleton;
}

/** 압축 해제 쓰레드를 재개시킵니다.
  */
void Pause::resume()
{
    sync.lock();
    pauseStatus = false;
    sync.unlock();
    pauseCond.wakeAll();
}

/** 압축 해제 쓰레드를 일시정지 시킵니다.
  */
void Pause::pause()
{
    sync.lock();
    pauseStatus = true;
    sync.unlock();
}

/** 일시정지 할 위치를 지정합니다.
  만약 일시정지 하게되었고, 이 지점을 만나게 되면 쓰레드가 일시정지되게 됩니다.\n
  */
void Pause::setPausePoint()
{
    sync.lock();
    if(pauseStatus){
        //resume 메소드를 호출할때까지 대기.
        pauseCond.wait(&sync);
    }
    sync.unlock();
}
