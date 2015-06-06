#include <QColor>
#include <QFrame>
#include <QPalette>
#include <QTextOption>
#include "qwraplabel.hpp"

/** 생성자.
  */
QWrapLabel::QWrapLabel(
        QWidget *parent
        ) :
    QTextEdit(parent)
{
    // label처럼 보이도록 만들기
    QPalette pal;
    this->setReadOnly(true);
    this->setFrameStyle(QFrame::NoFrame);
    pal.setColor(QPalette::Base, QColor(Qt::transparent));
    this->setPalette(pal);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAcceptRichText(false);

    // 줄바꿈 설정 및 크기 설정
    this->setLineWrapMode(QTextEdit::WidgetWidth);
    this->setWordWrapMode(QTextOption::WrapAnywhere);

    connect(this, SIGNAL( needShrink() ), this, SLOT( shrink() ));
}

/** 평문 텍스트를 설정합니다.\n
  설정 후, 이 위젯이 포함된 위젯의 높이를 재조정해야 합니다.
  */
void QWrapLabel::setPlainText(
        const QString &text ///< 텍스트
        )
{
    QTextEdit::setPlainText(text);
    emit needShrink();
}

void QWrapLabel::shrink()
{
    this->setMinimumHeight(document()->size().height());
}

void QWrapLabel::resizeEvent(
        QResizeEvent *event
        )
{
    QTextEdit::resizeEvent(event);
    emit needShrink();
}

QSize QWrapLabel::minimumSizeHint() const
{
    int w = QTextEdit::minimumSizeHint().width();
    int h = document()->size().height();
    return QSize(w, h);
}

QSize QWrapLabel::sizeHint() const
{
    int w = QTextEdit::sizeHint().width();
    int h = document()->size().height();
    return QSize(w, h);
}
