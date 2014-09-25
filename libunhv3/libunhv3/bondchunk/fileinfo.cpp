#include "unhv3.hpp"
#include "bondchunkattr.hpp"
#include "fileinfo.hpp"

/** 생성자.
  */
FileInfo::FileInfo() :
    FINF_("FINF")
{
}

/** FileInfo 역직렬화 수행자.
  @throw 포멧 경계가 잘못된 경우 BondReadException를 던집니다.
  */
QDataStream& operator>>(
        QDataStream &in, ///< 데이터 스트림
        FileInfo &fileInfo ///< 파일 정보 객체
        )
{
    in >> fileInfo.FINF_;

    quint32 max = fileInfo.FINF_.attrSize();
    quint32 s = 0;
    BondChunkAttr attr;
    while ( s < max ) {
        in >> attr;

        QString name =  attr.attrName();
        if ( name == "NAME" ) {
            fileInfo.NAME_ = attr.convertFromString();
        }
        else if ( name == "POS4" ) {
            fileInfo.POS4_ = attr.convertFromDword();
        }
        else if ( name == "CRC3" ) {
            fileInfo.CRC3_ = attr.convertFromDword();
        }
        else if ( name == "COMP" ) {
            fileInfo.COMP_ = attr.convertFromDword();
        }

        s += attr.chunkSize();
    }

    return in;
}

/** 파일 정보 청크 헤더를 얻습니다.
  @return 파일 정보 청크 헤더
  */
BondChunkHeader FileInfo::FINF() const
{
    return FINF_;
}

/** 파일명을 얻습니다.
  @return 파일명
  */
QString FileInfo::NAME() const
{
    return NAME_;
}

/** hv3파일에서의 파일 청크 위치를 얻습니다.
  @return hv3파일에서의 파일 청크 위치
  */
uint FileInfo::POS4() const
{
    return POS4_;
}

/** 파일 데이터에 대한 CRC32를 얻습니다.
  @return 파일 데이터에 대한 CRC32
  */
uint FileInfo::CRC3() const
{
    return CRC3_;
}

/** 파일에 대한 압축 방법을 얻습니다.
  @return 파일에 대한 압축 방법(0: 저장, 1~: 예약됨)
  */
uint FileInfo::COMP() const
{
    return COMP_;
}
