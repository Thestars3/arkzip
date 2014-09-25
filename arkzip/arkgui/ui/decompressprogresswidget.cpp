#include <QTimer>
#include <QCloseEvent>
#include <QInputDialog>
#include <QSystemTrayIcon>
#include "ui_DecompressProgressWidget.h"
#include "qwraplabel.hpp"
#include "reportgui.hpp"
#include "trayicon.hpp"
#include "pause.hpp"
#include "decompressprogresswidget.hpp"

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

    //암호 설정 시그널이 발생되면 진행창에서 암호 입력 창을 띄우도록 한다.
    QObject::connect(dynamic_cast<ReportGui*>(Report::getInstance()), SIGNAL(getPasswordSignal(QString*)), this, SLOT(getPassword(QString*)));

    //infoBrowser에 출력되는 메시지가 박스 경계에서 줄바꿈 되도록 함.
    ui->infoBrowser->setWordWrapMode(QTextOption::WrapAnywhere);

    // < -- 버튼 설정 -- >
    pauseIcon = QIcon::fromTheme(QString::fromUtf8("media-playback-pause"));
    pauseText = trUtf8("일시정지");
    playIcon = QIcon::fromTheme(QString::fromUtf8("media-playback-start"));
    playText = trUtf8("재개");
    closeIcon = QIcon::fromTheme(QString::fromUtf8("window-close"));
    closeText = trUtf8("닫기");
    arrowUp = QIcon::fromTheme(QString::fromUtf8("go-up"));
    arrowDown = QIcon::fromTheme(QString::fromUtf8("go-down"));

    // < -- 압축 해제 상태 반영 시그널과 슬롯을 연결 -- >
    {
        ReportGui *report = dynamic_cast<ReportGui*>(Report::getInstance());
        connect(report, SIGNAL( changeCurrentPercent(int) ), ui->partProgress, SLOT( setValue(int) ));
        connect(report, SIGNAL( changeTotalPercent(int) ), ui->totalProgress, SLOT( setValue(int) ));
        connect(report, SIGNAL( setArchiveInfoSignal(QString) ), ui->archaiveFileName, SLOT( setPlainText(const QString&) ));
        connect(report, SIGNAL( setExtractFileNameSignal(QString) ), ui->extractFileName, SLOT( setPlainText(const QString&) ));
        connect(report, SIGNAL( appendMessage(QString) ), ui->infoBrowser, SLOT( append(QString) ));
    }

    // < -- 오류 내용 숨김/보이기 버튼 설정 -- >
    toggleShowErrorInfo();
    connect(ui->toggleShowErrorInfo, SIGNAL( clicked() ), this, SLOT( toggleShowErrorInfo() ));

    // < -- 닫기 버튼 설정 -- >
    ui->closeBtn->setText(closeText);
    ui->closeBtn->setIcon(closeIcon);

    // < -- 일시정지 버튼 설정 -- >
    ui->pauseBtn->setIcon(pauseIcon);
    connect(ui->pauseBtn, SIGNAL( clicked() ), this, SLOT( togglePause() ));

    // < -- 트레이 아이콘 설정 -- >
    tray = new TrayIcon(this);
    tray->show();
}

void DecompressProgressWidget::getPassword(
        QString *password   ///< 설정된 암호가 입력되어야 할 변수
        )
{
    QInputDialog inputDialog;

    //트레이 아이콘 일부 기능을 비활성화 시킴.
    {
        tray->actionShow->setEnabled(false);
        tray->actionPauseToggle->setEnabled(false);
    }

    //입력 대화창 설정
    {
        inputDialog.setInputMode(QInputDialog::TextInput);
        inputDialog.setTextEchoMode(QLineEdit::PasswordEchoOnEdit);
        inputDialog.setWindowTitle( trUtf8("암호가 필요합니다.") );
        inputDialog.setLabelText( trUtf8("암호는?") );
        inputDialog.setModal(true);
    }

    //모달 대화창을 띄움.
    int s = inputDialog.exec();

    //입력 대화창 종료 상태에 따른 암호 설정
    switch(s){
    case QDialog::Accepted:
        *password = inputDialog.textValue();
        break;

    case QDialog::Rejected:
        *password = QString::null;
        break;
    }

    //트레이 아이콘 일부 기능을 활성화 시킴.
    {
        tray->actionShow->setEnabled(true);
        tray->actionPauseToggle->setEnabled(true);
    }

    //압축 해제 쓰레드 재개.
    Pause::getInstance()->resume();
}

/** 위젯 크기를 재조정합니다.
  */
void DecompressProgressWidget::shrink()
{
    if ( ui->infoBrowser->isHidden() ){
        resize(this->geometry().width(), minimumHeight());
    }
    else {
        resize(this->geometry().width(), oldWinHeight);
    }
    //adjustSize();
}

/** 에러 메시지 숨김/보이기 상태를 토글합니다.
  */
void DecompressProgressWidget::toggleShowErrorInfo()
{
    //만약 오류 내용이 숨김 상태라면
    if ( ui->infoBrowser->isHidden() ){
        {
            int h = height();
            if ( h != minimumHeight() ) {
                oldWinHeight = h;
            }
        }
        ui->verticalSpacer->changeSize(0, 0, QSizePolicy::Ignored, QSizePolicy::Ignored);
        ui->infoBrowser->show();
        ui->toggleShowErrorInfo->setIcon(arrowUp);
        ui->toggleShowErrorInfo->setText(trUtf8("작업 내역 숨기기"));
        QTimer::singleShot(0, this, SLOT(shrink()));
    }
    //만약 오류 내용이 보기 상태라면
    else {
        oldWinHeight = size().height();
        ui->verticalSpacer->changeSize(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
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
    //창 숨김 상태를 토글합니다.

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

/** 창 닫김 이벤트를 처리합니다.
  */
void DecompressProgressWidget::closeEvent(
        QCloseEvent *e ///< 종료 이벤트
        )
{
    e->accept();
    QTimer::singleShot(0, QApplication::instance(), SLOT(quit()));
}

/** 압축 해제가 종료되면 호출되는 메소드.
  */
void DecompressProgressWidget::finished(
        int exitCode   ///< 종료 코드
        )
{
    if ( exitCode == 0 ) {
        close();
    }
    else {
        ui->pauseBtn->hide();
        tray->actionPauseToggle->setVisible(false);
        if ( ui->infoBrowser->isHidden() ) {
            toggleShowErrorInfo();
        }
    }
}

/** 소멸자.
  */
DecompressProgressWidget::~DecompressProgressWidget()
{
    delete ui;
}
