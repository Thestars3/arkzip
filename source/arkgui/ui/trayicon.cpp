#include "trayicon.hpp"
#include "decompressprogresswidget.hpp"
#include <QMenu>
#include <QAction>
#include <QApplication>

/** 트레이 아이콘 생성자.
  */
TrayIcon::TrayIcon(
        QObject *parent ///< 부모 객체
        ) :
    QSystemTrayIcon(parent)
{
    //메뉴 생성
    menu = new QMenu();

    decompressProgressWidget = (DecompressProgressWidget*)parent;

    //아이콘 설정
    this->setIcon(QApplication::windowIcon());

    //숨김 메뉴 이벤트 설정
    {
        actionShow = new QAction(trUtf8("작업 진행 창 숨기기"), menu);
        actionShow->setCheckable(true);
        actionShow->setChecked(false);
        menu->addAction(actionShow);
        connect(actionShow, SIGNAL( toggled(bool) ), decompressProgressWidget, SLOT( toggleShow() ));
    }

    //일시정지 메뉴 이벤트 설정
    {
        actionPauseToggle = new QAction(decompressProgressWidget->pauseText, menu);
        actionPauseToggle->setIcon( decompressProgressWidget->pauseIcon );
        menu->addAction(actionPauseToggle);
        connect(actionPauseToggle, SIGNAL( triggered() ), decompressProgressWidget, SLOT( togglePause() ));
    }

    //닫기 메뉴 이벤트 설정
    {
        actionClose = new QAction(decompressProgressWidget->closeText, menu);
        actionClose->setIcon(decompressProgressWidget->closeIcon);
        menu->addAction(actionClose);
        connect(actionClose, SIGNAL( triggered() ), decompressProgressWidget, SLOT( close() ));
    }

    //메뉴 등록
    this->setContextMenu(menu);
}

/** 트레이 아이콘 소멸자.
  */
TrayIcon::~TrayIcon()
{
    delete menu;
}
