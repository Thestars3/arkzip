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

#ifndef CODECONV_HPP
#define CODECONV_HPP

#include <QString>
#include <functional>

/** 코드페이지 변환기.
  코드페이지 문제(ARK 라이브러리 코드 페이지 지정 무시 현상)의 해결을 위해 만들어졌습니다.
  */
class CodeConv
{
private:
    CodeConv();
    class QTextCodec *conv;                                               ///< 변환기
    std::function<QString(const struct SArkFileItem *pFileItem)> convert; ///< 변환 명령
    static CodeConv *singleton;                                           ///< 싱글톤

public:
    static CodeConv* getInstance();
    QString toQString(const struct SArkFileItem *pFileItem);
    bool setCodepage(const QString &codepageName);

};

#endif // CODECONV_HPP
