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

#ifndef REPORTGUI_HPP
#define REPORTGUI_HPP

#include <QObject>
#include "report.hpp"

/** 사용자에게 작업 현황을 gui로 보고합니다.
  */
class ReportGui :
        public QObject,
        public Report
{
    Q_OBJECT

public:
    explicit ReportGui(QObject *parent = 0);
    virtual ~ReportGui();

private:
    QString decompressFileName;   ///< 압축 해제 중인 부분 파일 명

public:
    virtual void reportTotalPercent(float);
    virtual void reportCurrentPercent(float);
    virtual void customSetStartFile(int, QString);
    virtual void customSetExtractFileStart(QString);
    virtual void setExtractPath(QString);
    virtual void setSeperatedExtractPath(QString);
    virtual void setWarning(QString);
    virtual void setCritical(QString);
    virtual void setMakeFailSeperatedFolder(const QString &archiveFilePath, const QString &defaultSavePath);
    virtual void setEndFile();
    virtual void setOpenFileError(QString);
    virtual void setDecompressError(QString archiveFilePath, QString partFilePath, QString errorMessage);
    virtual void setPartEnd();
    virtual void reportSkipLockFile(QString);
    virtual void setNewName(QString);
    virtual QString getPassword();

signals:
    void getPasswordSignal(QString*);         ///< 암호 입력 대화창을 띄우는 신호.
    void changeTotalPercent(int);             ///< 전체 진행율
    void changeCurrentPercent(int);           ///< 부분 진행율
    void setArchiveInfoSignal(QString);       ///< 압축 파일 명
    void setExtractFileNameSignal(QString);   ///< 압축 해제 파일 명
    void appendMessage(QString);              ///< info에 메시지 추가

};

#endif // REPORTGUI_HPP
