#include "ArkLibrary.hpp"
#include "arkerrconverter.hpp"
#include <QObject>

ArkErrConverter *ArkErrConverter::singleton = new ArkErrConverter(); ///< 싱글톤

/** 전역 객체를 얻습니다.
  @return 전역 객체
  */
ArkErrConverter* ArkErrConverter::getInstance()
{
    return singleton;
}

/** ARKERR 오류코드 -> 오류 문자열 해쉬 맵 초기화.
  */
ArkErrConverter::ArkErrConverter()
{
    arkErrHash.insert(ARKERR_NOERR, QObject::trUtf8("오류가 없습니다."));
    arkErrHash.insert(ARKERR_CANT_OPEN_FILE, QObject::trUtf8("파일을 여는데 실패 했습니다."));
    arkErrHash.insert(ARKERR_CANT_READ_SIG, QObject::trUtf8("시그니처를 읽는데 실패했습니다."));
    arkErrHash.insert(ARKERR_AT_READ_CONTAINER_HEADER, QObject::trUtf8("컨테이너 헤더가 손상 되었습니다."));
    arkErrHash.insert(ARKERR_INVALID_FILENAME_LENGTH, QObject::trUtf8("파일명 길이에 문제가 있습니다."));
    arkErrHash.insert(ARKERR_READ_FILE_NAME_FAILED, QObject::trUtf8("파일이름을 읽는데 실패 했습니다."));
    arkErrHash.insert(ARKERR_INVALID_EXTRAFIELD_LENGTH, QObject::trUtf8("확장 필드의 길이를 알 수 없습니다."));
    arkErrHash.insert(ARKERR_READ_EXTRAFILED_FAILED, QObject::trUtf8("확장 필드를 읽는데 실패했습니다."));
    arkErrHash.insert(ARKERR_CANT_READ_CENTRAL_DIRECTORY_STRUCTURE, QObject::trUtf8("중앙 디렉토리 정보를 읽는데 실패하였습니다. (zip 포멧)"));
    arkErrHash.insert(ARKERR_INVALID_FILENAME_SIZE, QObject::trUtf8("파일명 길이 정보가 잘못되었습니다."));
    arkErrHash.insert(ARKERR_INVALID_EXTRAFIELD_SIZE, QObject::trUtf8("확장 필드 정보 길이가 잘못되었습니다. (zip 포멧)"));
    arkErrHash.insert(ARKERR_INVALID_FILECOMMENT_SIZE, QObject::trUtf8("Comment 정보 길이가 잘못되었습니다."));
    arkErrHash.insert(ARKERR_CANT_READ_CONTAINER_HEADER, QObject::trUtf8("컨테이너의 헤더에 문제가 있습니다."));
    arkErrHash.insert(ARKERR_MEM_ALLOC_FAILED, QObject::trUtf8("메모리 할당에 실패했습니다."));
    arkErrHash.insert(ARKERR_CANT_READ_DATA, QObject::trUtf8("압축 데이타 읽기에 실패했습니다."));
    arkErrHash.insert(ARKERR_INFLATE_FAILED, QObject::trUtf8("Inflate 함수 호출중 오류가 발생했습니다."));
    arkErrHash.insert(ARKERR_USER_ABORTED, QObject::trUtf8("사용자가 작업을 중단하였습니다.")); //사용자 중지
    arkErrHash.insert(ARKERR_INVALID_FILE_CRC, QObject::trUtf8("압축 해제후 CRC 오류가 발생하였습니다."));
    arkErrHash.insert(ARKERR_UNKNOWN_COMPRESSION_METHOD, QObject::trUtf8("모르는(혹은 지원하지 않는) 압축방식입니다."));
    arkErrHash.insert(ARKERR_PASSWD_NOT_SET, QObject::trUtf8("암호걸린 파일인데 암호가 지정되지 않았습니다."));
    arkErrHash.insert(ARKERR_INVALID_PASSWD, QObject::trUtf8("암호가 틀렸습니다."));
    arkErrHash.insert(ARKERR_WRITE_FAIL, QObject::trUtf8("파일 쓰다가 실패했습니다."));
    arkErrHash.insert(ARKERR_CANT_OPEN_DEST_FILE, QObject::trUtf8("대상 파일을 만들 수 없습니다."));
    arkErrHash.insert(ARKERR_BZIP2_ERROR, QObject::trUtf8("BZIP2 압축해제중 오류가 발생했습니다."));
    arkErrHash.insert(ARKERR_INVALID_DEST_PATH, QObject::trUtf8("목적지 경로를 알수 없습니다. 경로명에 ../ 이 포함된 경우, 대상 경로에 접근이 불가능한 경우에 이러한 문제가 발생합니다."));
    arkErrHash.insert(ARKERR_CANT_CREATE_FOLDER, QObject::trUtf8("경로 생성에 실패했습니다."));
    arkErrHash.insert(ARKERR_DATA_CORRUPTED, QObject::trUtf8("압축푸는데 데이타가 손상되었거나 RAR 분할 압축파일의 뒷부분이 없습니다."));
    arkErrHash.insert(ARKERR_CANT_OPEN_FILE_TO_WRITE, QObject::trUtf8("쓰기용으로 파일 열기에 실패했습니다."));
    arkErrHash.insert(ARKERR_INVALID_INDEX, QObject::trUtf8("압축풀 대상의 index 파라메터가 잘못되었습니다."));
    arkErrHash.insert(ARKERR_CANT_READ_CODEC_HEADER, QObject::trUtf8("압축 코덱의 헤더를 읽는데 오류가 있습니다."));
    arkErrHash.insert(ARKERR_CANT_INITIALIZE_CODEC, QObject::trUtf8("코덱 초기화에 실패했습니다."));
    arkErrHash.insert(ARKERR_LZMA_ERROR, QObject::trUtf8("LZMA 압축 해제중 오류가 발생하였습니다."));
    arkErrHash.insert(ARKERR_PPMD_ERROR, QObject::trUtf8("ppmd와 관련된 오류가 있습니다."));
    arkErrHash.insert(ARKERR_CANT_SET_OUT_FILE_SIZE, QObject::trUtf8("출력 파일의 크기를 지정할수 없습니다.")); //출력파일의 SetSize() 실패
    arkErrHash.insert(ARKERR_NOT_MATCH_FILE_SIZE, QObject::trUtf8("압축을 푼 파일 크기가 맞지 않습니다."));
    arkErrHash.insert(ARKERR_NOT_A_FIRST_VOLUME_FILE, QObject::trUtf8("분할 압축파일중 첫번째 파일이 아닙니다."));
    arkErrHash.insert(ARKERR_NOT_OPENED, QObject::trUtf8("파일이 열려있지 않습니다."));
    arkErrHash.insert(ARKERR_NOT_SUPPORTED_ENCRYPTION_METHOD, QObject::trUtf8("지원하지 않는 암호 방식입니다."));
    arkErrHash.insert(ARKERR_INTERNAL, QObject::trUtf8("알수 없는 내부 오류가 발생했습니다."));
    arkErrHash.insert(ARKERR_NOT_SUPPORTED_FILEFORMAT, QObject::trUtf8("지원하지 않는 파일 포맷입니다."));
    arkErrHash.insert(ARKERR_UNKNOWN_FILEFORMAT, QObject::trUtf8("압축파일이 아닙니다."));
    arkErrHash.insert(ARKERR_FILENAME_EXCED_RANGE, QObject::trUtf8("경로명이 너무 길어서 파일이나 폴더를 만들 수 없습니다."));
    arkErrHash.insert(ARKERR_LZ_ERROR, QObject::trUtf8("lz와 관련된 오류가 발생했습니다."));
    arkErrHash.insert(ARKERR_NOTIMPL, QObject::trUtf8("포함되지 않은 기능입니다.")); //not implemented
    arkErrHash.insert(ARKERR_DISK_FULL, QObject::trUtf8("파일을 쓰다가 실패했습니다."));
    arkErrHash.insert(ARKERR_FILE_TRUNCATED, QObject::trUtf8("파일의 뒷부분이 잘렸습니다."));
    arkErrHash.insert(ARKERR_CANT_DO_THAT_WHILE_WORKING, QObject::trUtf8("압축 해제 작업중에는 파일을 열거나 닫을 수 없습니다."));
    arkErrHash.insert(ARKERR_CANNOT_FIND_NEXT_VOLUME, QObject::trUtf8("분할 압축된 파일의 다음 파일을 찾을 수 없습니다."));
    arkErrHash.insert(ARKERR_NOT_ARCHIVE_FILE, QObject::trUtf8("압축파일이 아닙니다.")); //Open() 호출시 명백히 압축파일이 아닌 경우 발생
    arkErrHash.insert(ARKERR_USER_SKIP, QObject::trUtf8("사용자가 건너띄기 했습니다."));
    arkErrHash.insert(ARKERR_INVALID_PASSWD_OR_BROKEN_ARCHIVE, QObject::trUtf8("암호가 틀리거나 파일이 손상되었습니다. (rar 포멧)"));
    arkErrHash.insert(ARKERR_ZIP_LAST_VOL_ONLY, QObject::trUtf8("분할 zip 인데 마지막 zip 파일만 열려고 했습니다."));
    arkErrHash.insert(ARKERR_ACCESS_DENIED_TO_DEST_PATH, QObject::trUtf8("대상 폴더에 대해서 쓰기 권한이 없습니다."));
    arkErrHash.insert(ARKERR_NOT_ENOUGH_MEMORY, QObject::trUtf8("메모리가 부족합니다."));
    arkErrHash.insert(ARKERR_NOT_ENOUGH_MEMORY_LZMA_ENCODE, QObject::trUtf8("LZMA 압축중 메모리가 부족합니다."));
    arkErrHash.insert(ARKERR_NOT_SUPPORTED_OPERATION, QObject::trUtf8("지원하지 않는 작동입니다. ACE 파일을 IArkSimpleOutStream 를 이용해 압축해제할 경우 발생합니다."));
    arkErrHash.insert(ARKERR_CANT_CONVERT_FILENAME, QObject::trUtf8("파일명이 잘못되어서 유니코드 파일명으로 바꿀 수 없습니다. 이 오류는 posix 환경에서 iconv 사용시 코드페이지가 잘못된 경우 사용할 수 없는 문자 때문에 발생합니다."));
    arkErrHash.insert(ARKERR_TOO_LONG_FILE_NAME, QObject::trUtf8("파일명이 너무 길어서 처리할 수 없습니다."));
    arkErrHash.insert(ARKERR_TOO_LONG_FILE_NAME_AND_TRUNCATED, QObject::trUtf8("파일명이 너무 길어서 뒷부분이 잘렸습니다."));
    arkErrHash.insert(ARKERR_TOO_MANY_FILE_COUNT, QObject::trUtf8("파일 갯수가 너무 길어서 처리할 수 없습니다."));
    arkErrHash.insert(ARKERR_CORRUPTED_FILE, QObject::trUtf8("파일이 손상되었습니다."));
    arkErrHash.insert(ARKERR_INVALID_FILE, QObject::trUtf8("포맷이 다릅니다."));
    arkErrHash.insert(ARKERR_CANT_READ_FILE, QObject::trUtf8("파일을 읽을 수 없습니다."));
    arkErrHash.insert(ARKERR_INVALID_VERSION, QObject::trUtf8("헤더파일과 dll 의 버전이 맞지 않습니다."));
    arkErrHash.insert(ARKERR_ENCRYPTED_BOND_FILE, QObject::trUtf8("압축 해제 불가능합니다. 이 파일은 암호화된 bond 파일입니다."));
    arkErrHash.insert(ARKERR_7ZERR_BROKEN_ARCHIVE, QObject::trUtf8("7z.dll 으로 열때 오류가 발생했습니다. 이 파일은 깨진파일입니다."));
    arkErrHash.insert(ARKERR_LOAD_7Z_DLL_FAILED, QObject::trUtf8("7z.dll 열다가 오류가 발생했습니다."));
    arkErrHash.insert(ARKERR_CANT_CREATE_FILE, QObject::trUtf8("파일을 쓰기용으로 생성하지 못합니다."));
    arkErrHash.insert(ARKERR_INIT_NOT_CALLED, QObject::trUtf8("Init() 함수가 호출되지 않았습니다."));
    arkErrHash.insert(ARKERR_INVALID_PARAM, QObject::trUtf8("잘못된 파라메터로 호출하였습니다."));
    arkErrHash.insert(ARKERR_CANT_OPEN_INPUT_SFX, QObject::trUtf8("SFX 파일을 열지 못합니다."));
    arkErrHash.insert(ARKERR_SFX_SIZE_OVER_4GB, QObject::trUtf8("SFX 파일의 크기가 4GB를 넘었습니다."));
    arkErrHash.insert(ARKERR_CANT_LOAD_ARKLGPL, QObject::trUtf8("ArkXXLgpl.dll 파일을 열지 못합니다."));
    arkErrHash.insert(ARKERR_CANT_STORE_FILE_SIZE_OVER_4GB, QObject::trUtf8("파일 크기가 4GB를 넘어서 저장할 수 없습니다."));
    arkErrHash.insert(ARKERR_ALREADY_DLL_CREATED, QObject::trUtf8("이미 ARK DLL 파일을 로드하였습니다.")); //CArkLib
    arkErrHash.insert(ARKERR_LOADLIBRARY_FAILED, QObject::trUtf8("LoadLibrary() 함수를 호출하는데 실패했습니다.")); //CArkLib
    arkErrHash.insert(ARKERR_GETPROCADDRESS_FAILED, QObject::trUtf8("GetProcAddress() 함수를 호출하는데 실패했습니다.")); //CArkLib
    arkErrHash.insert(ARKERR_UNSUPPORTED_OS, QObject::trUtf8("지원하지 않는 os입니다.")); //CArkLib
    arkErrHash.insert(ARKERR_LIBRARY_NOT_LOADED, QObject::trUtf8("라이브러리를 로드하지 않았거나 로드하는데 실패하였습니다.")); //CArkLib
}

/** ARKERR 열거자형 변수에 대한 오류 메시지를 얻습니다.
  @return ARKERR 열거자형 변수에 대한 오류 메시지.
  */
QString ArkErrConverter::getMessage(ARKERR nErr)
{
    return arkErrHash.value(nErr);
}
