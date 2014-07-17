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

#pragma once

#include <QWidget>
#include <QIcon>

namespace Ui {
class DecompressProgressWidget;
}

class DecompressProgressWidget :
        public QWidget
{
    Q_OBJECT
    
public:
    explicit DecompressProgressWidget(QWidget *parent = 0);
    ~DecompressProgressWidget();
    
private:
    Ui::DecompressProgressWidget *ui;   ///< ui 정보
    class TrayIcon *tray;               ///< 트레이 아이콘
    int oldWinHeight;                   ///< 작업 로그 보이기를 수행할시, 복구될 창의 높이

private:
    void closeEvent(QCloseEvent*);

public:
    QIcon pauseIcon;   ///< 일시정지 아이콘
    QString pauseText; ///< 일시정지 텍스트
    QIcon playIcon;    ///< 시작 아이콘
    QString playText;  ///< 시작 텍스트
    QIcon closeIcon;   ///< 닫기 아이콘
    QString closeText; ///< 닫기 텍스트
    QIcon arrowUp;     ///< 위 화살표
    QIcon arrowDown;   ///< 아래 화살표

public slots:
    void togglePause();
    void toggleShow();
    void toggleShowErrorInfo();
    void shrink();
    void finished(int);
    void getPassword(QString*);

};
