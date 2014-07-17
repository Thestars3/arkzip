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

#include <QtGui/QApplication>
#include <QTimer>
#include "ui/decompressprogresswidget.hpp"
#include "decompressgui.hpp"
#include <QIcon>
#include "reportgui.hpp"

/** 프로그램을 시작합니다.
  @return 종료코드. 문제가 있다면 0이 아닌 값을 반환하게 됩니다.
  */
int main(
        int argc,
        char *argv[]
        )
{
    QApplication application(argc, argv);

    //어플리케이션 아이콘을 지정합니다.
    {
        QIcon icon;
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/16x16/apps/arkzip.png"), QSize(16, 16));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/20x20/apps/arkzip.png"), QSize(20, 20));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/22x22/apps/arkzip.png"), QSize(22, 22));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/24x24/apps/arkzip.png"), QSize(24, 24));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/32x32/apps/arkzip.png"), QSize(32, 32));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/36x36/apps/arkzip.png"), QSize(36, 36));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/48x48/apps/arkzip.png"), QSize(48, 48));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/64x64/apps/arkzip.png"), QSize(64, 64));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/72x72/apps/arkzip.png"), QSize(72, 72));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/96x96/apps/arkzip.png"), QSize(96, 96));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/128x128/apps/arkzip.png"), QSize(128, 128));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/192x192/apps/arkzip.png"), QSize(192, 192));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/256x256/apps/arkzip.png"), QSize(256, 256));
        icon.addFile(QString::fromUtf8("/usr/share/icons/hicolor/scalable/apps/arkzip.svg"));
        application.setWindowIcon(icon);
    }

    //decompress의 부모를 어플리케이션으로 지정하여 어플리케이션이 종료되었을때, 삭제되도록 합니다.
    DecompressGui decompress(argc, argv, &application);

    qDebug("%s", "DecompressProgressWidget 객체 생성");
    DecompressProgressWidget progressWidget;

    //decompress 객체의 finished 시그널이 발생했을떄, 진행창 위젯의 finished 메소드를 호출하도록 합니다.
    QObject::connect(&decompress, SIGNAL(finished(int)), &progressWidget, SLOT(finished(int)));

    //어플리케이션 이벤트 루프에서 decompress가 실행되도록 합니다.
    QTimer::singleShot(0, &decompress, SLOT(start()));

    qDebug("%s", "어플리케이션 이벤트 루프에서 DecompressProgressWidget이 보여지도록 합니다.");
    QTimer::singleShot(0, &progressWidget, SLOT(show()));

    //qt 어플리케이션의 이벤트 루프가 시작됩니다.
    application.exec();

    if ( decompress.isWorkEnd() && decompress.isRunning() ) {
        //압축 해제 쓰레드가 끝날때가 까지 대기.
        decompress.wait();
    }

    return decompress.getExitcode();
}
