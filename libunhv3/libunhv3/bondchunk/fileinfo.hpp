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

#ifndef FILEINFO_HPP
#define FILEINFO_HPP

#include <QDataStream>
#include "bondchunkheader.hpp"

class FileInfo
{
private:
    BondChunkHeader FINF_; ///< File Info
    QString NAME_;         ///< File Name
    uint POS4_;            ///< "FILE" chunk position of file
    uint CRC3_;            ///< crc32 of file data
    uint COMP_;            ///< Compression Method of file(0: store, 1~: reserved)
    friend QDataStream& operator>>(QDataStream &in, FileInfo &fileInfo);

public:
    FileInfo();

    // < -- Getter -- >
    BondChunkHeader FINF() const;
    QString NAME() const;
    uint POS4() const;
    uint CRC3() const;
    uint COMP() const;

};

QDataStream& operator>>(QDataStream &in, FileInfo &fileInfo);

#endif // FILEINFO_HPP
