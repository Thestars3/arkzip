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

#ifndef DECOMPRESSGUI_HPP
#define DECOMPRESSGUI_HPP

#include "decompress.hpp"

/** 압축 해제 처리를 수행.
  */
class DecompressGui :
        public Decompress
{
public:
    DecompressGui(int&, char*[], QObject *parent = 0);

private:
    virtual void processOption();

};

#endif // DECOMPRESSGUI_HPP
