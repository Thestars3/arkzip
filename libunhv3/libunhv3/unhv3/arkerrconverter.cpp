#include "arkerrconverter.hpp"

/** 주어진 Unhv3Status를 주어진 Unhv3Status에 대응하는 적당한 ARKERR로 바꿔줍니다.
  @return 주어진 Unhv3Status에 대응하는 ARKERR
  */
ARKERR ArkerrConverter::ConvertUnhv3Status(
        const Unhv3Status &status ///< 상태
        )
{
    switch ( status.status() ) {
    case Unhv3Status::NO_ERROR:
        return ARKERR_NOERR;

    case Unhv3Status::FILE_NOT_EXIST:
        return ARKERR_CANT_OPEN_FILE;

    case Unhv3Status::CANT_READ_FILE:
        return ARKERR_CANT_OPEN_FILE;

    case Unhv3Status::NOT_HV3_FORMAT:
        return ARKERR_UNKNOWN_FILEFORMAT;

    case Unhv3Status::CRC_ERROR:
        return ARKERR_INVALID_FILE_CRC;

    case Unhv3Status::SAVEPATH_NOT_EXIST:
        return ARKERR_CANT_CREATE_FOLDER;

    case Unhv3Status::SAVEPATH_IS_NOT_DIR:
        return ARKERR_CANT_CREATE_FOLDER;

    case Unhv3Status::NOT_YET_IMPELEMENTED:
        return ARKERR_NOTIMPL;

    case Unhv3Status::SAVE_FILE_ERROR:
        return ARKERR_WRITE_FAIL;

    case Unhv3Status::IS_BROKEN_FILE:
        return ARKERR_AT_READ_CONTAINER_HEADER;

    case Unhv3Status::TARGET_IS_DIR:
        return ARKERR_CANT_OPEN_DEST_FILE;

    case Unhv3Status::NOT_SUPORTED_DECRIPT_METHODE:
        return ARKERR_ENCRYPTED_BOND_FILE;
    }

    return ARKERR_NOERR;
}
