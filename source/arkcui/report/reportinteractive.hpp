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

#ifndef REPORINTERACTIVE_HPP
#define REPORINTERACTIVE_HPP

#include <QTextStream>
#include <QObject>
#include "report.hpp"

/** 사용자에게 텍스트를 통해 작업 현황을 보고합니다.
  @example [1/5] ./test.zip\n
           \t testfolder/a.txt\n
           \t\t 작업 현황 30%\n
           오류가 발생했습니다. 파일이 손상되었습니다.\n
           \t testfoloder/b.txt\n
           \t\t 암호는? *****
           \t\t 작업 현황 50%\n
           \t 전체 현황 100%\n

           [1/2] ./test2.zip\n
  */
class ReportInteractive :
        public Report,
        public QObject
{
public:
    ReportInteractive(QObject* = 0);
    virtual ~ReportInteractive();

private:
    class Terminal {
    public:
        const static QString reset;
        const static QString deleteLine;
        const static QString red;
        const static QString yellow;
        const static QString green;
    };

private:
    QTextStream stdout;           ///< 표준 출력
    QTextStream stdin;            ///< 표준 입력
    QTextStream stderr;           ///< 표준 오류

public:
    virtual void setTotalPercent(float);
    virtual void reportCurrentPercent(float);
    virtual void customSetStartFile(int, QString);
    virtual void customSetExtractFileStart(QString);
    virtual void setExtractPath(QString);
    virtual void setWarning(QString);
    virtual void setCritical(QString);
    virtual void setEndFile();
    virtual void reportSkipLockFile(QString);
    virtual void setSeperatedExtractPath(QString);
    virtual void setPartEnd();
    virtual void setNewName(QString);
    virtual QString getPassword();

};

#endif // REPORINTERACTIVE_HPP
