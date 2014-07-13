#include "decompressprogresswidget.hpp"
#include "ui_DecompressProgressWidget.h"
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include "reportgui.hpp"
#include "pause.hpp"
#include "trayicon.hpp"
#include <QCloseEvent>
#include <QTimer>

/** 생성자.
  */
DecompressProgressWidget::DecompressProgressWidget(
        QWidget *parent ///< 부모 위젯
        ) :
    QWidget(parent),
    ui(new Ui::DecompressProgressWidget)
{
    ui->setupUi(this);

    //이곳에 추가적인 초기화 명령을 입력합니다.

    pauseIcon = QIcon::fromTheme(QString::fromUtf8("media-playback-pause"));
    pauseText = trUtf8("일시정지");
    playIcon = QIcon::fromTheme(QString::fromUtf8("media-playback-start"));
    playText = trUtf8("재개");
    closeIcon = QIcon::fromTheme(QString::fromUtf8("window-close"));
    closeText = trUtf8("닫기");
    arrowUp = QIcon::fromTheme(QString::fromUtf8("go-up"));
    arrowDown = QIcon::fromTheme(QString::fromUtf8("go-down"));

    //압축 해제 상태 반영 시그널과 슬롯을 연결
    {
        ReportGui *report = (ReportGui*)Report::getInstance();
        connect(report, SIGNAL( changeCurrentPercent(int) ), ui->partProgress, SLOT( setValue(int) ));
        connect(report, SIGNAL( changeTotalPercent(int) ), ui->totalProgress, SLOT( setValue(int) ));
        connect(report, SIGNAL( setArchiveInfoSignal(QString) ), ui->archaiveFileName, SLOT( setText(QString) ));
        connect(report, SIGNAL( setExtractFileNameSignal(QString) ), ui->extractFileName, SLOT( setText(QString) ));
        connect(report, SIGNAL( appendMessage(QString) ), ui->infoBrowser, SLOT( append(QString) ));
    }

    //오류 내용 숨김/보이기 버튼 설정
    {
        toggleShowErrorInfo();
        connect(ui->toggleShowErrorInfo, SIGNAL( clicked() ), this, SLOT( toggleShowErrorInfo() ));
    }

    //닫기 버튼 설정
    {
        ui->closeBtn->setText(closeText);
        ui->closeBtn->setIcon(closeIcon);
    }

    //일시정지 버튼 설정
    {
        ui->pauseBtn->setIcon(pauseIcon);
        connect(ui->pauseBtn, SIGNAL( clicked() ), this, SLOT( togglePause() ));
    }

    // 트레이 아이콘 설정
    {
        tray = new TrayIcon(this);
        tray->show();
    }

    qDebug("%s", "DecompressProgressWidget 객체 생성완료");
}

/** 위젯 크기를 재조정합니다.
  @note 이 함수가 호출되면 기존 수직 크기에 대한 정보는 소실됩니다.
  */
void DecompressProgressWidget::shrink()
{
    resize(this->geometry().width(), minimumHeight());
    //adjustSize();
}

/** 에러 메시지 숨김/보이기 상태를 토글합니다.
  */
void DecompressProgressWidget::toggleShowErrorInfo()
{
    //만약 오류 내용이 숨김 상태라면
    if ( ui->infoBrowser->isHidden() ){
        ui->infoBrowser->show();
        ui->toggleShowErrorInfo->setIcon(arrowUp);
        ui->toggleShowErrorInfo->setText(trUtf8("작업 내역 숨기기"));
    }
    //만약 오류 내용이 보기 상태라면
    else {
        ui->infoBrowser->hide();
        ui->toggleShowErrorInfo->setIcon(arrowDown);
        ui->toggleShowErrorInfo->setText(trUtf8("작업 내역 보이기"));
    }
    QTimer::singleShot(0, this, SLOT(shrink()));
}

/** 창 숨김 상태를 토글합니다.
  */
void DecompressProgressWidget::toggleShow()
{
    qDebug("%s", "창 숨김 상태를 토글합니다.");
    //숨김 상태인 경우
    if ( this->isHidden() ){
        this->show();
        tray->actionShow->setChecked(false);
    }
    //숨김 상태가 아닌 경우
    else {
        this->hide();
        tray->actionShow->setChecked(true);
    }
}

/** 일시정지 상태를 토글합니다.
  */
void DecompressProgressWidget::togglePause()
{
    //일시정지 상태일 경우
    if ( Pause::getInstance()->isPaused() ) {
        Pause::getInstance()->resume();

        //트레이 메뉴 설정.
        tray->actionPauseToggle->setText(pauseText);
        tray->actionPauseToggle->setIcon(pauseIcon);

        //버튼 설정
        ui->pauseBtn->setText(pauseText);
        ui->pauseBtn->setIcon(pauseIcon);
    }
    // 일시정지 상태가 아닌 경우
    else {
        Pause::getInstance()->pause();

        //트레이 메뉴 설정.
        tray->actionPauseToggle->setText(playText);
        tray->actionPauseToggle->setIcon(playIcon);

        //버튼 설정
        ui->pauseBtn->setText(playText);
        ui->pauseBtn->setIcon(playIcon);
    }
}

/** 창 닫김 이벤트.
  */
void DecompressProgressWidget::closeEvent(
        QCloseEvent *event  ///< 창 닫김 이벤트
        )
{
    emit closed();
    event->accept();
}

/** 소멸자.
  */
DecompressProgressWidget::~DecompressProgressWidget()
{
    delete ui;
}
