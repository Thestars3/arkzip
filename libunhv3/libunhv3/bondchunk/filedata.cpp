#include <QFile>
#include "ufp.hpp"
#include "bondreadexception.hpp"
#include "filedata.hpp"

/** 생성자.
  */
FileData::FileData() :
    FILE_("FILE")
{
}

/** FileData 역직렬화 수행자.
  @throw 포멧 경계가 잘못된 경우 BondReadException를 던집니다.
  */
QDataStream& operator>>(
        QDataStream &in, ///< 데이터 스트림
        FileData &fileData ///< 파일 데이터 객체
        )
{
    uint len;
    fileData.pos_ = in.device()->pos();
    in >> fileData.FILE_;
    len = fileData.FILE_.chunkDataSize();

    // raw_data
    fileData.raw_data_pos = in.device()->pos();
    fileData.raw_data_len = len;
    if ( in.skipRawData(len) == -1 ) {
        throw BondReadException();
    }

    return in;
}

/** 파일 데이터 청크를 얻습니다.
  @return 파일 데이터 청크
  */
BondChunkHeader FileData::FILE() const
{
    return FILE_;
}

/** 파일 데이터를 얻습니다.
  @throw 파일 경계가 잘못되었을 경우 BondReadException를 던집니다.
  @return 파일 데이터.
  */
QByteArray FileData::raw_data(
        QFile *device ///< 읽어올 파일이 저장된 장치
        ) const
{
    QByteArray raw_data;
    QDataStream fileStream(device);
    fileStream.setByteOrder(QDataStream::ByteOrder::LittleEndian);

//    device->seek(raw_data_pos);

    fileStream.device()->seek(raw_data_pos);
    if ( ! ufp::readBytes(fileStream, raw_data, raw_data_len) ) {
        throw BondReadException();
    }

    return raw_data;
}

/** 압축 파일 내에서의 파일 데이터 위치를 반환합니다.
  @return 압축 파일 내에서의 파일 데이터 위치
  */
quint64 FileData::pos() const
{
    return pos_;
}
