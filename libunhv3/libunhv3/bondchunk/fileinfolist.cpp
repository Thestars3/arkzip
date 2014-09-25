#include <QVectorIterator>
#include "fileinfo.hpp"
#include "fileinfolist.hpp"

/** FileInfoList 역직렬화 수행자.
  @throw 포멧 경계가 잘못된 경우 BondReadException를 던집니다.
  */
QDataStream& operator>>(
        QDataStream &in, ///< 데이터 스트림
        FileInfoList &fileInfoList ///< 파일 정보 목록 객체
        )
{
    in >> fileInfoList.LIST_;
    uint size = 0;
    uint max = fileInfoList.LIST_.subChunkSize();
    while ( size < max ) {
        FileInfo *fileInfo = new FileInfo();
        in >> (*fileInfo);
        fileInfoList.fileInfoList_.push_back(fileInfo);
        size += fileInfo->FINF().attrSize() + BondChunkHeader::CHUNK_SIZE;
    }
    return in;
}

/** 생성자.
  */
FileInfoList::FileInfoList() :
    LIST_("LIST")
{
}

/** 전체 아이템 개수를 얻습니다.
  @return 전체 아이템 개수
  */
int FileInfoList::getFileItemCount() const
{
    return fileInfoList_.count();
}

/** 지정된 인덱스의 파일 정보 객체 주소를 얻습니다.
  @return 지정된 인덱스의 파일 정보 객체 주소
  */
const FileInfo* FileInfoList::getFileItem(
        int index ///< 얻을 파일의 인덱스
        ) const
{
    return fileInfoList_.at(index);
}
