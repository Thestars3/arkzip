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

#ifndef OPTION_HPP
#define OPTION_HPP

#include <QList>
#include <QObject>
#include <QTextStream>
#include <boost/program_options.hpp>
#include "codepage/codepagelist.hpp"

/** 옵션을 처리합니다.
  */
class Option :
        public QObject
{
public:
    Option(int &argc, char *argv[]);
    void process();

private:
    boost::program_options::variables_map analyze();
    void printHelp();
    void printVersionPage();
    void exec(const std::string&, QVector<std::string>);

    int argc_;                                                           ///< 인자 수
    char **argv_;                                                        ///< 인자 배열
    boost::program_options::options_description desc;                     ///< 전체 옵션 정의
    boost::program_options::options_description visibleDesc;              ///< 보여줄 옵션들
    boost::program_options::positional_options_description positional;    ///< 옵션 위치
    QTextStream stderr;                                                   ///< 표준 에러
    CodepageList codepageList;                                            ///< 코드 페이지 목록
    const static std::string ARKZIP_CUI_PATH;                             ///< arkcui 실행 파일 경로
    const static std::string ARKZIP_GUI_PATH;                             ///< arkgui 실행 파일 경로

};

#endif // OPTION_HPP
