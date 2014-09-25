#include <QFile>
#include <QImage>
#include <QRegExp>
#include <QFileInfo>
#include <QDataStream>
#include "bondreadexception.hpp"
#include "bondchunkheader.hpp"
#include "filedatastorage.hpp"
#include "arkerrconverter.hpp"
#include "bondchunkattr.hpp"
#include "fileinfolist.hpp"
#include "unhv3event.hpp"
#include "ufp.hpp"
#include "unhv3.hpp"

/** 현재 열려있는 HV3 파일이 암호화된 파일을 포함하고 있는지 여부를 확인합니다.
  @return 암호화 사용 여부.
  */
bool Unhv3::isEncrypted() const
{
    if ( ENCR_ != 0 ) {
        return true;
    }

    return false;
}

/** 압축 해제중 발생하는 여러가지 이벤트를 받아서 처리하고 싶을 경우, 이벤트를 콜백으로 받을 객체를 지정합니다.\n
  nullptr을 넘겨주면, 이벤트 처리가 중단됩니다.
  @return 성공여부.
  */
void Unhv3::setEvent(
        IArkEvent *event ///< 이벤트를 받을 객체의 포인터
        )
{
    event_->setEvent(event);
}

/** 소멸자.
  */
Unhv3::~Unhv3()
{
    delete HV30_;
    delete LIST_;
    delete HEAD_;
    delete BODY_;
    delete file;
    delete event_;
    delete extension;
}

/** 특정 인덱스의 파일 데이터 크기를 가져옵니다.
  @return 특정 인덱스의 파일 데이터 크기
  */
quint32 Unhv3::fileDataSize(
        int index ///< 인덱스
        ) const
{
    return BODY_->getFileData(LIST_->getFileItem(index)->POS4())->FILE().chunkDataSize();
}

/** 생성자.
  */
Unhv3::Unhv3() :
    openStatus(false),
    status(Unhv3Status::NO_ERROR),
    VERS_(0),
    FSIZ_(0),
    DIRE_(0),
    ENCR_(0)
{
    LIST_ = new FileInfoList();
    BODY_ = new FileDataStorage();
    HV30_ = new BondChunkHeader("HV30");
    HEAD_ = new BondChunkHeader("HEAD");
    file = new QFile();
    event_ = new Unhv3Event();
    extension = new QRegExp("\\.hdp$", Qt::CaseInsensitive);
    fileStream_.setByteOrder(QDataStream::LittleEndian);
}

/** 마지막으로 발생한 오류의 상세 내용을 확인한다.
  @return 상태코드.
  */
Unhv3Status Unhv3::lastError() const
{
    return status;
}

/** 마지막으로 발생한 오류의 상세 내용을 확인한다.
  @return 상태코드에 대응되는 ARKERR.
  */
int Unhv3::convertedLastError() const
{
    return static_cast<int>(ArkerrConverter::ConvertUnhv3Status(status));
}

/** 메모리로 직접 해제해 보면서 파일의 손상 여부를 확인합니다.
  @return 파일의 손상여부
  */
bool Unhv3::testArchive() const
{
    event_->setOpen();
    for (int index = 0, max = fileItemCount(); index < max; index++) {
        const FileInfo *fileItem = LIST_->getFileItem(index);
        QString filePathName = fileItem->NAME();
        QByteArray raw_data;

        event_->setStartFile(filePathName);
        event_->setProgress(0);

        // < -- 데이터를 메모리에 로드 -- >
        try {
            uint pos = fileItem->POS4();
            raw_data = BODY_->getFileData(pos)->raw_data(file);
        }
        catch (BondReadException&) {
            status = Unhv3Status::IS_BROKEN_FILE;
            return false;
        }
        event_->setProgress(35);

        // < -- 복호화 -- >
        if ( ! decrypt(filePathName, raw_data) ) {
            return false;
        }
        event_->setProgress(75);

        // < -- CRC-32 -- >
        if ( ufp::computeCrc32(raw_data) != fileItem->CRC3() ) {
            status = Unhv3Status::CRC_ERROR;
            event_->setError(filePathName, status);
            return false;
        }
        event_->setProgress(99);
    }
    event_->setComplete();
    return false;
}

/** open 메소드로 파일을 분석 할때, 체크썸이 올바른지 확인합니다.
  @return 파일 손상 여부
  */
bool Unhv3::isBrokenArchive() const
{
    if ( FSIZ_ != file->size()  ) {
        return true;
    }

    return false;
}

/** 현재 열려있는 파일의 경로명을 리턴합니다.
  @return 파일의 경로명. 열려있지 않으면 QString::null을 리턴.
  */
QString Unhv3::filePathName() const
{
    if ( isOpened() ) {
        return file->fileName();
    }
    else {
        return QString::null;
    }
}

/** 현재 파일이 열려있는 상태인지 여부를 확인합니다.
  @return true : 열림; false : 안열림.
  */
bool Unhv3::isOpened() const
{
    return openStatus;
}

/** 지정된 경로에 파일을 모두 푼다.
  @return 성공여부.
  */
bool Unhv3::extractAllTo(
        const QString &savePath ///< 저장 경로
        ) const
{
    QFileInfo pathInfo(savePath);
    bool success = true;

    if ( ! pathInfo.exists() ) {
        status = Unhv3Status::SAVEPATH_NOT_EXIST;
        return false;
    }

    if ( ! pathInfo.isDir() ) {
        status = Unhv3Status::SAVEPATH_IS_NOT_DIR;
        return false;
    }

    event_->setOpen();
    int max = fileItemCount();
    for (int i = 0; i < max; i++) {
        if ( ! extractOneTo(i, savePath) ) {
            success = false;
        }
    }
    event_->setComplete();

    return success;
}

/** 현재 열려있는 파일의 파일 크기를 리턴합니다.
  @return 압축파일의 파일 크기. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
uint Unhv3::archiveFileSize() const
{
    return FSIZ_;
}

/** 현재 열려있는 파일의 HV3 포맷의 버전 정보를 리턴합니다.
  @return HV3 포맷의 버전 정보. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
uint Unhv3::formatVersion() const
{
    return VERS_;
}

/** 현재 열려있는 파일의 GUID를 리턴합니다.
  @return 파일의 GUID. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QUuid Unhv3::archiveGuid() const
{
    return GUID_;
}

/** 현재 열려있는 파일의 UUID를 리턴합니다.
  @return 파일의 UUID. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QUuid Unhv3::archiveUuid() const
{
    return UUID_;
}

/** 현재 열려있는 파일의 만들어진 시간을 리턴합니다.
  @return 파일이 만들어진 시간. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QDateTime Unhv3::createdTime() const
{
    return FTIM_;
}

/** 현재 열려있는 파일의 책의 제본방식을 리턴합니다.
  @return 책의 제본방식. 0: 정보없음, 1:left to right 2:right to left. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
uint Unhv3::direction() const
{
    return DIRE_;
}

/** 현재 열려있는 파일의 암호화 방식을 리턴합니다.
  @return 파일의 암호화 방식, 0:암호화 없음. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
uint Unhv3::encryptMethod() const
{
    return ENCR_;
}

/** 현재 열려있는 파일의 저작권 정보를 리턴합니다.
  @return 저작권 정보. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QString Unhv3::copyrightInformation() const
{
    return COPY_;
}

/** 현재 열려있는 파일의 관련 링크 URL을 리턴합니다.
  @return 관련 링크 URL. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QString Unhv3::relatedLink() const
{
    return LINK_;
}

/** 현재 열려있는 파일의 제목을 리턴합니다.
  @return 파일의 제목. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QString Unhv3::fileTitle() const
{
    return TITL_;
}

/** 현재 열려있는 파일의 책의 국제 표준 도서 번호 정보를 리턴합니다.
  @return 책의 ISBN 정보. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QString Unhv3::isbn() const
{
    return ISBN_;
}

/** 현재 열려있는 파일의 원 저작자를 리턴합니다.
  @return Original Writer. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QString Unhv3::originalWriter() const
{
    return WRTR_;
}

/** 현재 열려있는 파일의 출판인을 리턴합니다.
  @return Publisher. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QString Unhv3::publisher() const
{
    return PUBL_;
}

/** 현재 열려있는 파일의 원 출판 날자를 리턴합니다.
  @return Original Publishing date. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QString Unhv3::originalPublishingDate() const
{
    return DATE_;
}

/** 현재 열려있는 파일의 설명을 리턴합니다.
  @return Comment. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QString Unhv3::comment() const
{
    return COMT_;
}

/** 현재 열려있는 파일의 제작자를 리턴합니다.
  @return HV3 File maker. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QString Unhv3::fileMaker() const
{
    return MAKR_;
}

/** 현재 열려있는 파일의 장르를 리턴합니다.
  @return Genere. 만약, 아무 정보도 없다면 빈값을 반환한다.
  */
QString Unhv3::genere() const
{
    return GENR_;
}

/** 현재 열려있는 파일 내의 파일 아이템 갯수를 리턴합니다.
  @return 압축파일 내의 파일 아이템 갯수
  */
int Unhv3::fileItemCount() const
{
    return LIST_->getFileItemCount();
}

/** 특정 파일 아이템의 정보를 가져옵니다.
  @return 지정된 인덱스의 파일 아이템 정보
  */
const FileInfo* Unhv3::getFileItem(
        int index ///< 파일 아이템의 인덱스
        ) const
{
    return LIST_->getFileItem(index);
}

/** 압축파일내의 한개의 파일만을 풀때 사용합니다.
  @return true : 작업 성공; false : 작업 중 오류 있음.
  */
bool Unhv3::extractOneTo(
        int index,
        QString savePath ///< 저장될 경로
        ) const
{
    savePath += "/" + getFileItem(index)->NAME();
    return extractOneAs(index, savePath);
}

/** 암호화된 데이터를 복호화합니다.
  @return 성공여부. 만약, 지원하지 않은 복호화 종류라면 false를 반환합니다.
  */
bool Unhv3::decrypt(
        const QString &filePathName, ///< 파일 경로
        QByteArray &encryptedData    ///< 암호화된 데이터
        ) const
{
    switch(ENCR_) {
    case 2:
        for (int i = 0, size = encryptedData.size(); i < size; i++) {
            encryptedData[i] = encryptedData.at(i) ^ ( i % 256 );
        }
        break;

    default:
        status = Unhv3Status::NOT_SUPORTED_DECRIPT_METHODE;
        event_->setError(filePathName, status);
        return false;
    }

    return true;
}

/** 압축파일내의 한개의 파일만을 풀때 사용합니다. \n
  Unhv3::extractOneTo와 달리 파일명을 지정할 수 있습니다.\n
  저장될 파일경로에 포함된 저장파일명의 확장자는 원본 파일의 확장자에 따라 변할수 있습니다.\n
  중복 처리 이벤트가 설정되지 않았다면, 중복되는 경로에 있는 파일은 덮어 씌워지게 됩니다.
  @return true : 작업 성공; false : 작업 중 오류 있음.
  */
bool Unhv3::extractOneAs(
        int index,
        QString filePathName ///< 저장될 파일의 이름을 포함한 경로
        ) const
{
    const FileInfo *fileItem = LIST_->getFileItem(index);
    QByteArray raw_data;

    event_->setStartFile(filePathName);
    event_->setProgress(0);

    // < -- 데이터를 메모리에 로드 -- >
    try {
        uint pos = fileItem->POS4();
        raw_data = BODY_->getFileData(pos)->raw_data(file);
    }
    catch (BondReadException&) {
        status = Unhv3Status::IS_BROKEN_FILE;
        return false;
    }
    event_->setProgress(25);

    // < -- 복호화 -- >
    if ( ! decrypt(filePathName, raw_data) ) {
        return false;
    }
    event_->setProgress(50);

    // < -- CRC-32 -- >
    if ( ufp::computeCrc32(raw_data) != fileItem->CRC3() ) {
        status = Unhv3Status::CRC_ERROR;
        event_->setError(filePathName, status);
        return false;
    }
    event_->setProgress(70);

    // < -- 변환 및 저장 -- >
    {
        bool thisFileIsHv3 = fileItem->NAME().contains(*extension);
        bool hv3ConvertSuccess = false;

        // < -- 변환 후 저장 -- >
        if ( thisFileIsHv3 ) {
            QImage image = QImage::fromData(raw_data, "hdp");
            QString convertedPath = filePathName;
            bool imageHasAlphaChannel = image.hasAlphaChannel();

            if ( imageHasAlphaChannel ) {
                convertedPath.replace(*extension, ".png");
            }
            else {
                convertedPath.replace(*extension, ".jpg");
            }

            if ( event_ != nullptr && QFile::exists(convertedPath) ) {
                convertedPath = event_->convertDuplicatedName(convertedPath);
            }

            if ( imageHasAlphaChannel ) {
                hv3ConvertSuccess = image.save(convertedPath, "png");
            }
            else {
                hv3ConvertSuccess = image.save(convertedPath, "jpg", 100);
            }

            event_->setProgress(99);
        }

        // < -- 저장 -- >
        if ( ! thisFileIsHv3 || ! hv3ConvertSuccess ) {
            if ( event_ != nullptr && QFile::exists(filePathName) ) {
                filePathName = event_->convertDuplicatedName(filePathName);
            }

            QFile file(filePathName);

            if ( ! file.open(QFile::WriteOnly) ) {
                status = Unhv3Status::SAVE_FILE_ERROR;
                event_->setError(filePathName, status);
                return false;
            }

            if ( file.write(raw_data) == -1 ) {
                status = Unhv3Status::SAVE_FILE_ERROR;
                event_->setError(filePathName, status);
                file.close();
                return false;
            }
            event_->setProgress(99);

            file.close();
        }
    }

    event_->setProgress(100);
    return true;
}

/** filepath에 존재하는 hv3 파일을 엽니다.
  @return 성공 여부.
  */
bool Unhv3::open(
        const QString &filepath ///< 파일 경로
        )
{
    file->close();
    file->setFileName(filepath);
    file->open(QIODevice::ReadOnly);
    openStatus = true;
    fileStream_.setDevice(file);

    QFileInfo fileInfo(*file);

    if ( ! fileInfo.exists() ) {
        status = Unhv3Status::FILE_NOT_EXIST;
        return false;
    }

    if ( ! fileInfo.isReadable() ) {
        status = Unhv3Status::CANT_READ_FILE;
        return false;
    }

    if ( fileInfo.size() < 4 ) {
        status = Unhv3Status::NOT_HV3_FORMAT;
        return false;
    }

    // < -- HV30 -- >
    {
        try {
            fileStream_ >> *HV30_;
        }
        catch (BondReadException&) {
            status = Unhv3Status::NOT_HV3_FORMAT;
            return false;
        }

        quint32 max = HV30_->attrSize();
        quint32 s = 0;
        BondChunkAttr attr;
        while ( s < max ) {
            fileStream_ >> attr;

            QString name =  attr.attrName();
            if ( name == "VERS" ) {
                VERS_ = attr.convertFromDword();
            }
            else if ( name == "FSIZ" ) {
                FSIZ_ = attr.convertFromDword();
            }

            s += attr.chunkSize();
        }
    }

    // < -- HEAD -- >
    {
        try {
            fileStream_ >> *HEAD_;
        }
        catch (BondReadException&) {
            status = Unhv3Status::IS_BROKEN_FILE;
            return false;
        }

        quint32 max = HEAD_->attrSize();
        quint32 s = 0;
        BondChunkAttr attr;
        while ( s < max ) {
            fileStream_ >> attr;

            QString name =  attr.attrName();
            if ( name == "GUID" ) {
                GUID_ = attr.convertFromGuid();
            }
            else if ( name == "UUID" ) {
                UUID_ = attr.convertFromUuid();
            }
            else if ( name == "FTIM" ) {
                FTIM_ = attr.convertFromFiletime();
            }
            else if ( name == "DIRE" ) {
                DIRE_ = attr.convertFromDword();
            }
            else if ( name == "ENCR" ) {
                ENCR_ = attr.convertFromDword();
            }
            else if ( name == "COPY" ) {
                COPY_ = attr.convertFromString();
            }
            else if ( name == "LINK" ) {
                LINK_ = attr.convertFromString();
            }
            else if ( name == "TITL" ) {
                TITL_ = attr.convertFromString();
            }
            else if ( name == "ISBN" ) {
                ISBN_ = attr.convertFromString();
            }
            else if ( name == "WRTR" ) {
                WRTR_ = attr.convertFromString();
            }
            else if ( name == "PUBL" ) {
                PUBL_ = attr.convertFromString();
            }
            else if ( name == "DATE" ) {
                DATE_ = attr.convertFromString();
            }
            else if ( name == "COMT" ) {
                COMT_ = attr.convertFromString();
            }
            else if ( name == "MAKR" ) {
                MAKR_ = attr.convertFromString();
            }
            else if ( name == "GENR" ) {
                GENR_ = attr.convertFromString();
            }

            s += attr.chunkSize();
        }
    }

    // < -- LIST, BODY -- >
    try {
        fileStream_ >> *LIST_ >> *BODY_;
    }
    catch (BondReadException&) {
        status = Unhv3Status::IS_BROKEN_FILE;
        return false;
    }

    status = Unhv3Status::NO_ERROR;
    return true;
}
