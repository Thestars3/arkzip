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

#ifndef FILEDATA_HPP
#define FILEDATA_HPP

#include <QByteArray>
#include <QDataStream>
#include "bondchunkheader.hpp"

class FileData
{
private:
    BondChunkHeader FILE_;    ///< 파일 데이터 청크, 속성청크는 가지지 않는다.
    quint64 raw_data_pos;     ///< 파일 상에서의 데이터 시작 위치
    uint raw_data_len;        ///< 데이터 크기
    quint64 pos_;             ///< 이 청크의 시작 오프셋.
    friend QDataStream& operator>>(QDataStream &in, FileData &fileData);

public:
    FileData();

    // < -- Getter -- >
    quint64 pos() const;
    BondChunkHeader FILE() const;
    QByteArray raw_data(class QFile *device) const;

};

QDataStream& operator>>(QDataStream &in, FileData &fileData);

#endif // FILEDATA_HPP
