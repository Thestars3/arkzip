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

#ifndef QWRAPLABEL_HPP
#define QWRAPLABEL_HPP

#include <QSize>
#include <QObject>
#include <QString>
#include <QResizeEvent>
#include <QTextEdit>

/** 문자 단위로 줄바꿈이 일어나는 label 객체를 제공합니다.\n
 QLabel이 단어 단위의 줄바꿈만 지원하는 관계로, QTextEdit 객체를 상속받아 QLabel처럼 보이도록 만듦.
 */
class QWrapLabel :
        public QTextEdit
{
    Q_OBJECT

public:
    QWrapLabel(QWidget *parent = 0);
    virtual QSize minimumSizeHint() const;
    virtual QSize sizeHint() const;
    virtual void resizeEvent(QResizeEvent *event);

public slots:
    void shrink();
    void setPlainText(const QString &text);

};

#endif // QWRAPLABEL_HPP
