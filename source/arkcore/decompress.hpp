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

#ifndef DECOMPRESS_HPP
#define DECOMPRESS_HPP

#include <QThread>
#include <functional>
#include <boost/program_options.hpp>

/** 압축 해제에 관한 전반적인 작업을 처리합니다.
  압축 해제 작업의 진행 상태에 대한 정보는 report 싱글톤 객체를 통해 reportinterface를 상속받은 객체에 넘겨주기만 합니다.
  */
class Decompress :
        public QThread
{
    Q_OBJECT
public:
    explicit Decompress(QObject *parent = 0);
    ~Decompress();
    QString getSaveDirPath() const;
    void setPassword(const QString&);
    QString getCurrentFilePath() const;
    class CArkEvent* getArkEvent();
    int getExitcode();
    bool isWorkEnd();

private:
    class CArkLib *arkLib;                                             ///< 압축 해제 처리 객체(전방 선언됨)
    class CArkEvent *arkEvent;                                         ///< 압축 해제 이벤트 처리(전방 선언됨)
    QVector<class QFile*> *files;                                      ///< 파일 목록
    std::function<void(const QString&)> decompress;                    ///< 압축 해제를 처리하는 함수객체
    std::function<QString(const QString &filePath)> getSaveDirPath_;   ///< 저장할 경로를 얻습니다.
    std::function<void(QString)> setSeperatedExtractPath;              ///< 분할된 저장 경로를 설정합니다. --sperate
    std::function<void()> setExtractPath;                              ///< 기본 저장 경로를 설정합니다. --out-dir
    QString currentFilePath_;                                          ///< 현재 압축 해제중인 파일의 경로
    int totalFileCount_;                                               ///< 전체 압축 파일의 수
    int exitcode;                                                      ///< 종료코드
    bool isWorkEnd_;                                                   ///< 모든 압축 해제 작업이 완료되었다.
    QString password_;                                                 ///< 설정된 암호
    const static char *ARK_LIBRARY_PATH;

    //옵션 처리
protected:
    boost::program_options::options_description optionDesc;                    ///< 옵션 설명
    boost::program_options::variables_map optionVm;                            ///< 분석된 옵션 맵
    boost::program_options::positional_options_description optionPositional;   ///< 옵션 위치 설정
    virtual void analyzeOption(int&, char**);
    virtual void processOption();
    virtual void defineOption();
    void parseArgument(int&, char**);

private:
    void loadLibrary();
    void setOption();

protected:
    void run();

signals:
    void finished(int);

};

#endif // DECOMPRESS_HPP
