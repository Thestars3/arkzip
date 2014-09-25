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

#ifndef BONDCHUNKHEADER_HPP
#define BONDCHUNKHEADER_HPP

#include <QDataStream>

/** 청크 헤더
  */
class BondChunkHeader
{
private:
    QString chunkName_;       ///< 청크의 이름
    quint32 attrSize_;        ///< 속성 청크의 크기
    quint32 subChunkSize_;    ///< 모든 하위 청크의 크기의 합
    quint32 chunkDataSize_;   ///< 현재 청크의 데이타 크기
    friend QDataStream& operator>>(QDataStream &in, BondChunkHeader &bondChunkHeader);

public:
    explicit BondChunkHeader(const QString &chunkName);

    const static uint CHUNK_SIZE; ///< 청크 자체의 크기

    // < -- Getter -- >
    QString chunkName() const;
    quint32 attrSize() const;
    quint32 subChunkSize() const;
    quint32 chunkDataSize() const;

};

QDataStream& operator>>(QDataStream &in, BondChunkHeader &bondChunkHeader);

#endif // BONDCHUNKHEADER_HPP
