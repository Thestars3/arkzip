#ifndef ARKERRCONVERTER_HPP
#define ARKERRCONVERTER_HPP

#include "unhv3status.hpp"

enum ARKERR
{
    ARKERR_NOERR										= 0x00,
    ARKERR_CANT_OPEN_FILE								= 0x01,		// 파일 열기 실패
    ARKERR_CANT_READ_SIG								= 0x02,		// signature 읽기 실패
    ARKERR_AT_READ_CONTAINER_HEADER						= 0x03,		// 컨테이너 헤더가 손상되었음
    ARKERR_INVALID_FILENAME_LENGTH						= 0x04,		// 파일명 길이에 문제
    ARKERR_READ_FILE_NAME_FAILED						= 0x05,		// 파일이름 읽기 실패
    ARKERR_INVALID_EXTRAFIELD_LENGTH					= 0x06,		// extra field 읽기
    ARKERR_READ_EXTRAFILED_FAILED						= 0x07,		// extra field 읽기 실패
    ARKERR_CANT_READ_CENTRAL_DIRECTORY_STRUCTURE		= 0x08,		// (zip) Central Directory 정보를 읽는데 실패하였음
    ARKERR_INVALID_FILENAME_SIZE						= 0x09,		// 파일명 길이 정보가 잘못되었음
    ARKERR_INVALID_EXTRAFIELD_SIZE						= 0x10,		// (zip) ExtraField 정보 길이가 잘못되었음
    ARKERR_INVALID_FILECOMMENT_SIZE						= 0x11,		// Comment 정보 길이가 잘못되었음
    ARKERR_CANT_READ_CONTAINER_HEADER					= 0x12,		// 컨테이너의 헤더에 문제가 있음
    ARKERR_MEM_ALLOC_FAILED								= 0x13,		// 메모리 할당 실패
    ARKERR_CANT_READ_DATA								= 0x15,		// 압축 데이타 읽기 실패
    ARKERR_INFLATE_FAILED								= 0x16,		// Inflate 함수 호출중 에러 발생
    ARKERR_USER_ABORTED									= 0x17,		// 사용자 중지
    ARKERR_INVALID_FILE_CRC								= 0x18,		// 압축 해제후 CRC 에러 발생
    ARKERR_UNKNOWN_COMPRESSION_METHOD					= 0x19,		// 모르는(혹은 지원하지 않는) 압축방식
    ARKERR_PASSWD_NOT_SET								= 0x20,		// 암호걸린 파일인데 암호가 지정되지 않았음
    ARKERR_INVALID_PASSWD								= 0x21,		// 암호가 틀렸음
    ARKERR_WRITE_FAIL									= 0x30,		// 파일 쓰다가 실패
    ARKERR_CANT_OPEN_DEST_FILE							= 0x31,		// 대상 파일을 만들 수 없음
    ARKERR_BZIP2_ERROR									= 0x32,		// BZIP2 압축해제중 에러 발생
    ARKERR_INVALID_DEST_PATH							= 0x33,		// 경로명에 ../ 이 포함된 경우, 대상 경로에 접근이 불가능한 경우
    ARKERR_CANT_CREATE_FOLDER							= 0x34,		// 경로 생성 실패
    ARKERR_DATA_CORRUPTED								= 0x35,		// 압축푸는데 데이타가 손상됨 or RAR 분할 압축파일의 뒷부분이 없음
    ARKERR_CANT_OPEN_FILE_TO_WRITE						= 0x36,		// 쓰기용으로 파일 열기 실패
    ARKERR_INVALID_INDEX								= 0x37,		// 압축풀 대상의 index 파라메터가 잘못됨
    ARKERR_CANT_READ_CODEC_HEADER						= 0x38,		// 압축 코덱의 헤더를 읽는데 에러
    ARKERR_CANT_INITIALIZE_CODEC						= 0x39,		// 코덱 초기화 실패
    ARKERR_LZMA_ERROR									= 0x40,		// LZMA 압축 해제중 에러 발생
    ARKERR_PPMD_ERROR									= 0x41,		// ppmd 에러
    ARKERR_CANT_SET_OUT_FILE_SIZE						= 0x42,		// 출력파일의 SetSize() 실패
    ARKERR_NOT_MATCH_FILE_SIZE							= 0x43,		// 압축을 푼 파일 크기가 맞지 않음
    ARKERR_NOT_A_FIRST_VOLUME_FILE						= 0x44,		// 분할 압축파일중 첫번째 파일이 아님
    ARKERR_NOT_OPENED									= 0x45,		// 파일이 열려있지 않음
    ARKERR_NOT_SUPPORTED_ENCRYPTION_METHOD				= 0x46,		// 지원하지 않는 암호 방식
    ARKERR_INTERNAL										= 0x47,		// 내부 에러
    ARKERR_NOT_SUPPORTED_FILEFORMAT						= 0x48,		// 지원하지 않는 파일 포맷
    ARKERR_UNKNOWN_FILEFORMAT							= 0x49,		// 압축파일이 아님
    ARKERR_FILENAME_EXCED_RANGE							= 0x50,		// 경로명이 너무 길어서 파일이나 폴더를 만들 수 없음
    ARKERR_LZ_ERROR										= 0x52,		// lz 에러
    ARKERR_NOTIMPL										= 0x53,		// not implemented
    ARKERR_DISK_FULL									= 0x54,		// 파일 쓰다가 실패
    ARKERR_FILE_TRUNCATED								= 0x55,		// 파일의 뒷부분이 잘렸음
    ARKERR_CANT_DO_THAT_WHILE_WORKING					= 0x56,		// 압축 해제 작업중에는 파일을 열거나 닫을 수 없음
    ARKERR_CANNOT_FIND_NEXT_VOLUME						= 0x57,		// 분할 압축된 파일의 다음 파일을 찾을 수 없음
    ARKERR_NOT_ARCHIVE_FILE								= 0x58,		// 압축파일이 아님 (Open() 호출시 명백히 압축파일이 아닌 경우 발생)
    ARKERR_USER_SKIP									= 0x59,		// 사용자가 건너띄기 했음.
    ARKERR_INVALID_PASSWD_OR_BROKEN_ARCHIVE				= 0x60,		// 암호가 틀리거나 파일이 손상되었음 (rar 포맷)
    ARKERR_ZIP_LAST_VOL_ONLY							= 0x61,		// 분할 zip 인데 마지막 zip 파일만 열려고 했음
    ARKERR_ACCESS_DENIED_TO_DEST_PATH					= 0x62,		// 대상 폴더에 대해서 쓰기 권한이 없음
    ARKERR_NOT_ENOUGH_MEMORY							= 0x63,		// 메모리가 부족함
    ARKERR_NOT_ENOUGH_MEMORY_LZMA_ENCODE				= 0x64,		// LZMA 압축중 메모리가 부족함
    ARKERR_CANT_OPEN_SHARING_VIOLATION					= 0x65,		// 파일이 잠겨있어서 열 수 없음 (ERROR_SHARING_VIOLATION, WIN32 전용)
    ARKERR_CANT_OPEN_ERROR_LOCK_VIOLATION				= 0x66,		// 파일이 잠겨있어서 열 수 없음 (ERROR_LOCK_VIOLATION, WIN32 전용)
    ARKERR_CANT_LOAD_UNACE								= 0x67,		// unace32.exe 혹은 unacev2.dll 파일을 로드할 수 없음 (WIN32 전용)
    ARKERR_NOT_SUPPORTED_OPERATION						= 0x68,		// 지원하지 않는 작동입니다. (ACE 파일을 IArkSimpleOutStream 를 이용해 압축해제할 경우 발생)
    ARKERR_CANT_CONVERT_FILENAME						= 0x69,		// 파일명이 잘못되어서 유니코드 파일명으로 바꿀 수 없음(posix 환경에서 iconv 사용시 코드페이지가 잘못된 경우 사용할 수 없는 문자 때문에 발생)
    ARKERR_TOO_LONG_FILE_NAME							= 0x70,		// 파일명이 너무 길어서 처리할 수 없음
    ARKERR_TOO_LONG_FILE_NAME_AND_TRUNCATED				= 0x71,		// 파일명이 너무 길어서 뒷부분이 잘렸습니다.
    ARKERR_TOO_MANY_FILE_COUNT							= 0x72,		// 파일 갯수가 너무 길어서 처리할 수 없음

    ARKERR_CORRUPTED_FILE								= 0x100,	// 파일이 손상되었음
    ARKERR_INVALID_FILE									= 0x101,	// 포맷이 다르다
    ARKERR_CANT_READ_FILE								= 0x102,	// 파일을 읽을 수 없음

    ARKERR_INVALID_VERSION								= 0x200,	// 헤더파일과 dll 의 버전이 맞지 않음
    ARKERR_ENCRYPTED_BOND_FILE							= 0x201,	// 압축 해제 불가(암호화된 bond 파일임)

    ARKERR_7ZERR_BROKEN_ARCHIVE							= 0x300,	// 7z.dll 으로 열때 에러가 발생(깨진파일)
    ARKERR_LOAD_7Z_DLL_FAILED							= 0x301,	// 7z.dll 열다가 에러 발생

    ARKERR_CANT_CREATE_FILE								= 0x401,	// 파일을 쓰기용으로 생성하지 못함
    ARKERR_INIT_NOT_CALLED								= 0x402,	// Init() 함수가 호출되지 않았음
    ARKERR_INVALID_PARAM								= 0x403,	// 잘못된 파라메터로 호출하였음
    ARKERR_CANT_OPEN_INPUT_SFX							= 0x404,	// SFX 파일을 열지 못함
    ARKERR_SFX_SIZE_OVER_4GB							= 0x405,	// SFX 파일의 크기가 4GB를 넘었음
    ARKERR_CANT_LOAD_ARKLGPL							= 0x406,	// ArkXXLgpl.dll 파일을 열지 못함
    ARKERR_CANT_STORE_FILE_SIZE_OVER_4GB				= 0x407,	// 파일 크기가 4GB를 넘어서 저장할 수 없음

    ARKERR_ALREADY_DLL_CREATED							= 0x902,	// (CArkLib) 이미 ARK DLL 파일을 로드하였음
    ARKERR_LOADLIBRARY_FAILED							= 0x903,	// (CArkLib) LoadLibrary() 호출 실패
    ARKERR_GETPROCADDRESS_FAILED						= 0x904,	// (CArkLib) GetProcAddress() 호출 실패
    ARKERR_UNSUPPORTED_OS								= 0x905,	// (CArkLib) 지원하지 않는 os
    ARKERR_LIBRARY_NOT_LOADED							= 0x906,	// (CArkLib) 라이브러리를 로드하지 않았거나 로드하는데 실패하였음
};

class ArkerrConverter
{
public:
    static ARKERR ConvertUnhv3Status(const Unhv3Status &status);

};

#endif // ARKERRCONVERTER_HPP
