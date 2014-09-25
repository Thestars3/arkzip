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

#ifdef DEBUG
#include <QtGlobal>
#include <QByteArray>
#endif
#include <QtCore/QCoreApplication>
#include "option.hpp"

/** 프로그램을 시작합니다.
  @return 종료코드. 문제가 있다면 0이 아닌 값을 반환하게 됩니다.
  */
int main(
        int argc,
        char *argv[]
        )
{
    QCoreApplication app(argc, argv);

    // 디버깅시, 라이브러리 경로를 프로젝트 경로에서 찾습니다.
#ifdef DEBUG
    QByteArray pathEnv(qgetenv("LD_LIBRARY_PATH"));
    pathEnv += ":" + QByteArray(_ARKCORE_DIR_PATH);
    pathEnv += ":" + QByteArray(_LIBUNHV3_DIR_PATH);
    if ( ! qputenv("LD_LIBRARY_PATH", pathEnv) ) {
        qWarning("%s", "라이브러리 경로 설정에 실패했습니다!");
    }
#endif

    //옵션 객체의 처리 메소드가 수행되면 압축 해제를 수행할 프로그램과 이 프로그램은 exec됩니다.
    Option(argc, argv).process();

    //무언가 알수 없는 오류가 발생했습니다.
    return 1;
}
