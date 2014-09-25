#include "arklib.hpp"
#include <QDataStream>
#include "unhv3.hpp"

/** 압축파일 내의 모든 파일 아이템의 압축을 해제할 때 사용합니다.
  @return TRUE : 모든 파일의 압축을 성공적으로 풀었습니다. \nFALSE : 압축 해제중 에러가 1건 이상 발생하였습니다.
  */
BOOL32 ArkLib::ExtractAllTo(
        const QString &path ///< [in] 압축을 풀 경로를 지정합니다.
        )
{
    if ( ! unhv3_.isNull() ) {
        return unhv3_->extractAllTo(path);
    }

    return CArkLib::ExtractAllTo(path.toStdWString().c_str());
}

/** 사용중인 IArk 객체를 해제하고, 로드된 DLL을 언로드합니다.
  */
void ArkLib::Destroy()
{
    if ( ! unhv3_.isNull() ) {
        unhv3_ = nullptr;
    }

    iArkEvent_ = nullptr;
    CArkLib::Destroy();
}

/** 특정 파일 아이템의 정보를 가져옵니다.\n
  만약, hv3 파일을 열고 있다면, 리턴되는 구조체는 static입니다. 자료의 손실을 방지하려면 구조체를 복사해야 합니다.
  @return 지정된 인덱스의 파일 아이템 정보를 리턴합니다. 만일 입력된 인덱스가 범위를 벗어났거나, IArk::Open()메쏘드를 통해서 파일을 열지 않은 경우는 NULL을 리턴합니다.
  */
const SArkFileItem* ArkLib::GetFileItem(
        int index ///< [in] 압축파일 아이템의 인덱스를 지정합니다. 유효한 index 파라메터의 범위는 0 부터 IArk::GetFileItemCount()-1 까지 입니다.
        ) const
{
    if ( ! unhv3_.isNull() ) {
        if ( 0 > index || index >= GetFileItemCount() ) {
            return nullptr;
        }
        static SArkFileItem f;
        static std::wstring fileNameW;
        static std::string fileName;
        const FileInfo *info = unhv3_->getFileItem(index);
        QString n = info->NAME();
        fileName = n.toStdString();
        fileNameW = n.toStdWString();
        f.isUnicodeFileName = TRUE;
        f.ntfsFileTimes = nullptr;
        f.compressionMethod = ARK_COMPRESSION_METHOD_STORE;
        f.crc32 = info->CRC3();
        f.attrib = ARK_FILEATTR_FILE;
        f.encryptionMethod = ( unhv3_->isEncrypted() ? ARK_ENCRYPTION_METHOD_ETC : ARK_ENCRYPTION_METHOD_NONE );
        f.compressedSize = f.uncompressedSize = unhv3_->fileDataSize(index);
        f.fileTime = unhv3_->createdTime().toTime_t();
        f.fileCommentW = nullptr;
        f.fileNameW = const_cast<wchar_t*>(fileNameW.c_str());
        f.fileName = const_cast<char*>(fileName.c_str());
        return &f;
    }

    return CArkLib::GetFileItem(index);
}

/** 압축파일내의 한개의 파일만을 압축을 풀때 사용합니다. IArk::ExtractOneTo()와 달리 파일명을 지정할 수 있습니다.
  @return TRUE : 모든 파일의 압축을 성공적으로 풀었습니다. \nFALSE : 압축 해제중 에러가 발생하였습니다. 발생한 에러는 IArk::GetLastError() 메쏘드를 통해서 확인이 가능합니다.
  */
BOOL32 ArkLib::ExtractOneAs(
        int index,                   ///< [in] 압축을 해제할 파일의 인덱스를 지정합니다. 유효한 인덱스 파라메터는 0 부터 IArk::GetFileItemCount()-1 까지 입니다.
        const QString &filePathName  ///< [in] 압축을 해제할 이름을 지정합니다.
        )
{
    if ( ! unhv3_.isNull()  ) {
        return unhv3_->extractOneAs(index, filePathName);
    }

    return CArkLib::ExtractOneAs(index, filePathName.toStdWString().c_str(), nullptr);
}

/** IArk::Open() 메쏘드를 호출해서 열려 있던 압축파일의 모든 데이타를 파일을 생성하지 않고, 메모리로 직접 해제해 보면서 압축파일의 손상 여부를 확인합니다.
  @warning 압축파일 내부의 어떤 파일이 손상되었는지 여부와, 정확히 어떤 손상이 발생했는지 여부를 확인하고자 할 경우는 IArk::SetEvent()(section 3.2.21) 메쏘드를 사용하여 콜백 이벤트를 확인하여야 합니다.
  @return 압축파일의 손상여부를 확인합니다. 대부분의 압축파일은 내부 헤더에 압축된 파일의 CRC 정보를 가지고 있기 때문에, 이를 통해서 파일의 손상여부 확인이 가능합니다. 단, 일부 체크섬 정보를 가지고 있지 않는 파일(ISO 등)은 파일이 손상된 경우에도 문제를 확인할 수 없는 경우도 있습니다.
  */
BOOL32 ArkLib::TestArchive()
{
    if ( ! unhv3_.isNull() ) {
        return unhv3_->testArchive();
    }

    return CArkLib::TestArchive();
}

/**
  @return 압축파일 내의 파일 아이템 갯수를 리턴합니다. 이 함수를 호출하기 전 IArk::Open() 메쏘드로 압축파일을 열어야 합니다. "파일 아이템" 목록에는 파일 뿐만 아니라 폴더도 포함됩니다.
  */
int ArkLib::GetFileItemCount() const
{
    if ( ! unhv3_.isNull() ) {
        return unhv3_->fileItemCount();
    }

    return CArkLib::GetFileItemCount();
}

/** 현재 압축파일이 열려있는 상태인지 여부를 확인합니다.
  @return TRUE : 압축파일이 열려있습니다.\nFALSE :압축파일이 열려있지 않습니다.
  */
BOOL32 ArkLib::IsOpened() const
{
    if ( ! unhv3_.isNull() ) {
        return unhv3_->isOpened();
    }

    return CArkLib::IsOpened();
}

ArkLib::ArkLib()
{
    iArkEvent_ = nullptr;
}

/** 압축 해제중 발생하는 여러가지 이벤트를 받아서 처리하고 싶을 경우, 이벤트를 콜백으로 받을 객체를 지정합니다.
  @return TRUE : 성공하였습니다. \nFALSE : 실패하였습니다.
  */
BOOL32 ArkLib::SetEvent(
        IArkEvent *pProgress ///< [in] 이벤트를 받을 객체의 포인터를 지정합니다. 만일 이벤트를 더이상 받고 싶지 않을 경우는 NULL을 파라메터로 전달하면 됩니다
        )
{
    if ( ! unhv3_.isNull() ) {
        unhv3_->setEvent(pProgress);
        return true;
    }

    iArkEvent_ = pProgress;
    return CArkLib::SetEvent(pProgress);
}

/** 압축파일을 열고 목록을 읽어들입니다.
  @return TRUE : 압축파일을 성공적으로 열었습니다. \nFALSE : 압축파일을 열 수 없습니다. 자세한 에러 코드는 IArk::GetLastError() 메쏘드를 호출해서 알아볼 수 있습니다.
  */
BOOL32 ArkLib::Open(
        QFile *file ///< 파일 객체 포인터
        )
{
    if ( file == nullptr ) {
        qWarning("ArkLib::open(QFile*) 불러올 장치를 지정하지 않았습니다.");
        return FALSE;
    }

    file->open(QIODevice::ReadOnly);
    char head[4];
    qint64 readBytes = file->read(head, sizeof(head));
    const bool readOk = ( readBytes == sizeof(head) );
    file->close();

    QString name = file->fileName();
    if ( readOk ) {
        if ( head[0] == 'H' && head[1] == 'V' && head[2] == '3' && head[3] == '0' ) {
            unhv3_ = new Unhv3();
            unhv3_->setEvent(iArkEvent_);
            return unhv3_->open(name);
        }
    }

    return CArkLib::Open(name.toStdWString().c_str());
}

/** 암호걸린 파일의 압축을 풀 때 사용할 암호를 지정합니다.
  */
void ArkLib::SetPassword(
        const QString &password ///< [in] 암호를 지정합니다. NULL을 파라메터로 넘길 경우 기존에 지정된 암호는 지워집니다.
        )
{
    if ( ! unhv3_.isNull() ) {
        return;
    }

    CArkLib::SetPassword( password.toStdWString().c_str() );
}

/** IArk::Open() 메쏘드를 호출해서 열려 있던 압축파일의 핸들을 닫고, 파일 목록도 삭제합니다.
  */
void ArkLib::Close()
{
    unhv3_ = nullptr;

    CArkLib::Close();
}

/** 메쏘드 호출시 에러가 발생하였을 경우 에러에 대한 상세한 에러코드값을 확인합니다.
  @return 자세한 사항은 Ark.h 파일의 ARKERR 타입을 참고하세요.
  */
ARKERR ArkLib::GetLastError() const
{
    if ( ! unhv3_.isNull() ) {
        return static_cast<ARKERR>(unhv3_->convertedLastError());
    }

    return CArkLib::GetLastError();
}
