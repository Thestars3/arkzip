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

#include <QTextStream>
#include <QObject>
#include "report.hpp"

/** 사용자에게 텍스트를 통해 작업 현황을 보고합니다. 단, 편의를 위한 부가 정보는 제외하고, 필요한 정보만 제공합니다. ex) 색상 강조, 압축 해제 진행율 표시 등...
  */
class ReportInteractiveNoTerminal :
        public Report,
        public QObject
{
public:
	ReportInteractiveNoTerminal(QObject* = 0);
	virtual ~ReportInteractiveNoTerminal();

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
    virtual void setSeperatedExtractPath(QString);
    virtual void setOpenFileError(QString);
    virtual void setCritical(QString);
    virtual void setDecompressError(QString archiveFilePath, QString partFilePath, QString errorMessage);
    virtual void setEndFile();
    virtual void reportSkipLockFile(QString);
    virtual void setPartEnd();
    virtual void setNewName(QString);
    virtual QString getPassword();

};
