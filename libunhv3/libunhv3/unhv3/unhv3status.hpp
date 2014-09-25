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

#ifndef UNHV3STATUS_HPP
#define UNHV3STATUS_HPP

#include <QObject>
#include <QString>

/** unhv3 작업 상태.
  */
class Unhv3Status :
        private QObject
{
    Q_OBJECT

public:
    enum Status {
        NO_ERROR,                    ///< 오류 없음
        FILE_NOT_EXIST,              ///< 파일 존재하지 않음
        CANT_READ_FILE,              ///< 파일을 읽을수 없음
        NOT_HV3_FORMAT,              ///< hv3 포멧이 아님
        CRC_ERROR,                   ///< CRC 오류
        SAVEPATH_NOT_EXIST,          ///< 지정된 저장 경로가 존재하지 않음.
        SAVEPATH_IS_NOT_DIR,         ///< 지정된 저장 경로는 폴더가 아닙니다.
        NOT_YET_IMPELEMENTED,        ///< 아직 구현되지 않은 기능입니다.
        SAVE_FILE_ERROR,             ///< 파일 쓰기 실패.
        IS_BROKEN_FILE,              ///< 손상된 파일
        TARGET_IS_DIR,               ///< 저장 경로로 지정된 타겟이 디렉토리입니다.
        NOT_SUPORTED_DECRIPT_METHODE ///< 지원하지 않은 복호화 방법로 암호화된 파일입니다.
    };
    explicit Unhv3Status(Status status);
    Unhv3Status(const Unhv3Status &unhv3Status);
    Unhv3Status& operator=(const Status &status);
    QString message() const;
    Status status() const;

private:
    Status status_; ///< 상태 코드

};

#endif // UNHV3STATUS_HPP
