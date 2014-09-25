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

#ifndef FAILMAKEDIREXCEPTION_HPP
#define FAILMAKEDIREXCEPTION_HPP

#include <QtCore>

namespace ufp {

/** 디렉토리 생성 실패 오류.
  */
class FailMakeDirException :
        public QtConcurrent::Exception
{
public:
    void raise() const;
    FailMakeDirException* clone() const;
};

}

#endif // FAILMAKEDIREXCEPTION_HPP
