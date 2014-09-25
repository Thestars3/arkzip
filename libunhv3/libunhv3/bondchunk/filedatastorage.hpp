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

#ifndef FILEDATASTORAGE_HPP
#define FILEDATASTORAGE_HPP

#include <QVector>
#include <QDataStream>
#include "bondchunkheader.hpp"
#include "filedata.hpp"

class FileDataStorage
{
private:
    BondChunkHeader BODY_;               ///< 파일데이터를 담는 청크, 속성 청크는 가지지 않으며, 여러개의 하위 FILE 청크를 가진다.
    QVector<FileData*> fileDataStorage_; ///< 파일 데이터 컨테이너
    friend QDataStream& operator>>(QDataStream &in, FileDataStorage &fileDataStorage);

public:
    const FileData* getFileData(uint pos) const;
    ~FileDataStorage();
    FileDataStorage();

};

QDataStream& operator>>(QDataStream &in, FileDataStorage &fileDataStorage);

#endif // FILEDATASTORAGE_HPP
