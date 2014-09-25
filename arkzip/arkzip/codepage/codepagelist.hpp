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

#ifndef CODEPAGELIST_HPP
#define CODEPAGELIST_HPP

#include <QList>
#include <QByteArray>
#include "codepagegroup.hpp"

/** 사용가능한 코드페이지 목록.
  */
class CodepageList
        : public QList<CodepageGroup*>
{
private:
    CodepageGroup* ConverterName(const QByteArray &converterName);

public:
    CodepageList();
    ~CodepageList();
    CodepageGroup* findGroup(const QByteArray &name);
    bool contains(const QString &alias);
    QByteArray find(const QString &alias);
    void print();

};

#endif // CODEPAGELIST_HPP
