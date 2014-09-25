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

#ifndef BONDCHUNKATTR_HPP
#define BONDCHUNKATTR_HPP

#include <QUuid>
#include <QDateTime>
#include <QByteArray>
#include <QDataStream>

/** 속성 청크
  */
class BondChunkAttr
{
private:
    static class QTextCodec *textCodec; /// 텍스트 변환 코덱
    QString attrName_;       ///< 속성의 이름.
    QByteArray attrData_;    ///< 속성 데이터.
    friend QDataStream& operator>>(QDataStream &in, BondChunkAttr &bondChunkAttr);

public:
    const static uint CHUNK_SIZE; ///< 속성 청크에서 속성 데이터의 크기를 제외한 크기.

    BondChunkAttr();

    /** 이 청크 자체의 크기를 반환합니다.
      @return 이 청크의 전체 크기
      */
    inline uint chunkSize() const
    {
        return attrData_.size() + CHUNK_SIZE;
    }

    // < -- Getter -- >
    QString attrName() const;
    QByteArray attrData() const;

    // < -- 변환 메소드 -- >
    QString convertFromString() const;
    QDateTime convertFromFiletime() const;
    uint convertFromDword() const;
    QUuid convertFromGuid() const;
    QUuid convertFromUuid() const;

};

QDataStream& operator>>(QDataStream &in, BondChunkAttr &bondChunkAttr);

#endif // BONDCHUNKATTR_HPP
