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

#ifndef FILEINFOLIST_HPP
#define FILEINFOLIST_HPP

#include <QVector>
#include <QDataStream>
#include "bondchunkheader.hpp"
#include "fileinfo.hpp"

class FileInfoList
{
private:
    BondChunkHeader LIST_;            ///< 파일 정보 목록, 여러개의 하위 FINF 청크를 가진다.
    QVector<FileInfo*> fileInfoList_; ///< 파일 정보 컨테이너
    friend QDataStream& operator>>(QDataStream &in, FileInfoList &fileInfoList);

public:
    FileInfoList();
    const FileInfo* getFileItem(int index) const;
    int getFileItemCount() const;

};

QDataStream& operator>>(QDataStream &in, FileInfoList &fileInfoList);

#endif // FILEINFOLIST_HPP
