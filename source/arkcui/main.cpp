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

#include "decompresscui.hpp"
#include <QtCore/QCoreApplication>
#include <QTimer>

/** 프로그램을 시작합니다.
  @return 종료코드. 문제가 있다면 0이 아닌 값을 반환하게 됩니다.
  */
int main(
        int argc,          ///< 프로그램 인자 수
        char *argv[]       ///< 프로그램 인자 배열
        )
{
    QCoreApplication application(argc, argv);

    //decompress의 부모를 어플리케이션으로 지정하여 어플리케이션이 종료되었을때 삭제되도록 합니다.
    DecompressCui decompress(argc, argv, &application);

    //decompress 객체의 finished 시그널이 발생했을떄, 어플리케이션이 종료되도록 합니다.
    QObject::connect(&decompress, SIGNAL(finished()), &application, SLOT(quit()));

    //어플리케이션 이벤트 루프에서 decompress가 실행되도록 합니다.
    QTimer::singleShot(0, &decompress, SLOT(start()));

    //qt 어플리케이션의 이벤트 루프가 시작됩니다.
    application.exec();

    return decompress.getExitcode();
}
