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

#ifndef ARKERR_HPP
#define ARKERR_HPP

#include <QString>
#include <QHash>

// ArkLib.hpp 헤더파일에 정의된 매크로로 인한 문제를 방지하기 위해 열거자형 변수 전방 선언을 사용합니다.
enum ARKERR;

/** ARKERR 열거자형 변수에 대한 설명을 얻습니다.
  */
class ArkErrConverter
{
public:
    static ArkErrConverter* getInstance();
    QString getMessage(ARKERR);

private:
    static ArkErrConverter *singleton;
    ArkErrConverter();
    QHash<ARKERR, QString> arkErrHash;   ///< 해당 ARKERR에 해당되는 메시지를 값을 가집니다.

};

#endif // ARKERR_HPP
