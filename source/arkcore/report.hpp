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

#ifndef REPORT_HPP
#define REPORT_HPP

#include <QString>
#include <QTimer>

/** 압축 해제 작업 현황 보고 클래스.
  */
class Report
{
protected:
    virtual ~Report();
    Report();
    int getTotalArchiveCount();
    void setTotalTimerInterval(int);
    void setPartTimerInterval(int);

protected:
    QString currentFileName;      ///< 압축 파일명

private:
    static Report *singleton;
    int totalArchiveCount_;     ///< 전체 압축 파일 갯수
    QTimer partTimer;           ///< 압축 파일에서 압축 해제 중인 파일에 대한 압축해제 진행율을 표시하는 간격을 제어합니다.
    QTimer totalTimer;          ///< 압축 파일에서의 전체 압축 해제 진행율 표시 간격 제어.

public:
    static Report* getInstance();
    static void setInstance(Report*);
    void setTotalArchiveCount(int);
    void setCurrentPercent(float);
    void setTotalPercent(float);
    void setExtractFileStart(QString);
    void setStartFile(int, QString);

    //사용자에게 보고하는 모든 작업을 처리하는 가상 메소드.
public:
    virtual void setNewName(QString);
    virtual void setDecompressError(QString archiveFilePath, QString partFilePath, QString errorMessage);
    virtual void reportTotalPercent(float);
    virtual void customSetExtractFileStart(QString);
    virtual void customSetStartFile(int, QString);
    virtual void setOpenFileError(QString);
    virtual void setExtractPath(QString);
    virtual void setWarning(QString);
    virtual void setSeperatedExtractPath(QString);
    virtual void reportCurrentPercent(float);
    virtual QString getPassword();
    virtual void setCritical(QString);
    virtual void setEndFile();
    virtual void setPartEnd();
    virtual void reportSkipLockFile(QString);

};

#endif // REPORT_HPP
