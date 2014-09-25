/*Copyright (C) 2014  별님

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef PAUSE_HPP
#define PAUSE_HPP

#include <QMutex>
#include <QObject>
#include <QWaitCondition>

/** 일시정지 이벤트를 처리하는 클래스.
  */
class Pause :
        public QObject
{
	Q_OBJECT
	
    //조건 변수
private:
    QMutex sync;                 ///< 뮤텍스
    QWaitCondition pauseCond;    ///< 일시정지 대기 상태
    bool pauseStatus;            ///< 일시정지 설정 여부

private:
    explicit Pause(QObject *parent = 0);
    static Pause *singleton;

public:
	static Pause* getInstance();
    void setPausePoint();
    bool isPaused();

public slots:
    void pause();
    void resume();

};

#endif // PAUSE_HPP
