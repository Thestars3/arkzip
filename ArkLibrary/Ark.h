////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
///                                      Ark Library 5
/// 
/// ※ 만일 컴파일 오류등으로 인해서 이 파일을 수정하여야 하는 경우가 발생할 경우 
///    관련 내용을 꼭 알려주시기 바랍니다. 
///    알려주시면 매번 업데이트마다 사용자님이 헤더파일을 수정하는 불편이 발생하지 않도록 
///    전처리기등을 추가하도록 하겠습니다.
///
/// @author   parkkh
/// @date     Tuesday, December 22, 2009  9:22:23 AM
/// 
/// Copyright(C) 2008-2012 Bandisoft, All rights reserved.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _ARK_H_
#define _ARK_H_

// ArkLibrary 버전 (Ark.h 와 ArkXX.dll 파일의 버전이 동일한지 여부 판단용)
#define ARK_LIBRARY_VERSION								(0x50000000 + 0x00130424)


// 에러코드
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


// ARK FILE FORMAT
enum ARK_FF
{
	ARK_FF_ZIP,								// zip, zipx
	ARK_FF_ZIP_LASTVOLONLY,					// 분할 zip 파일의 마지막 볼륨 (파일이 하나만 존재할 경우)
	ARK_FF_ZIP_BANDIZIP_SFX,				// 반디집 sfx 
	ARK_FF_ALZ,
	ARK_FF_ALZ_SECONDVOL,					// 분할 alz 파일의 2번째 이후 압축파일
	ARK_FF_LZH,
	ARK_FF_RAR,
	ARK_FF_RAR_SECONDVOL,					// 분할 RAR 파일의 2번째 이후 압축파일
	ARK_FF_7Z,
	ARK_FF_7ZSPLIT,							// 7z 파일의 뒷부분이 잘렸고 확장자가 .001 인 파일 (.7z.001 ~ .7z.NNN)
	ARK_FF_7ZBROKEN,						// 7z 파일의 뒷부분이 잘렸거나 헤더가 손상된 파일
	ARK_FF_TAR,
	ARK_FF_CAB,
	ARK_FF_CAB_NOTFIRSTVOL,					// 
	ARK_FF_ISO,								// iso, joliet
	ARK_FF_IMG,								// clone cd img (img, ccd)
	ARK_FF_UDF,
	ARK_FF_UDFBROKEN,						// 뒷부분이 잘린 UDF 
	ARK_FF_SPLIT,							// 확장자가 .001 인 파일 (.001 ~ .NNN)
	ARK_FF_BOND,							// hv3
	ARK_FF_GZ,
	ARK_FF_BZ2,
	ARK_FF_LZMA,
	ARK_FF_BH,								// blakhole
	ARK_FF_EGG,
	ARK_FF_EGG_NOTFIRSTVOL,					// 분할 압축의 첫번째 볼륨이 아닌 파일
	ARK_FF_XZ,
	ARK_FF_WIM,								// raw 만 사용하는 wim
	ARK_FF_WIM_COMPRESSED,					// 압축된 wim, Windows 에서만 지원
	ARK_FF_FREEARC,							// FreeArc - 파일 목록열기만 지원
	ARK_FF_Z,								// .Z (unix compress)
	ARK_FF_ARJ,								// arj 
	ARK_FF_BAMSFX,							// 밤톨이 sfx
	ARK_FF_BAMSFX_NOTFIRSTVOL,				// 
	ARK_FF_TGZ,								// .tar.gz
	ARK_FF_TBZ,								// .tar.bz2
	ARK_FF_J2J,								// .j2j
	ARK_FF_J2JBROKEN,						// 뒷부분이 잘린 j2j
	ARK_FF_K2K,								// .k2k
	ARK_FF_NSIS,							// nsis exe

	ARK_FF_UNKNOWN				= 0x00ff,	// 알 수 없는 파일 포맷

	ARK_FF_UNSUPPORTED_FIRST	= 0x0100,	// 지원하지 않는 압축파일 포맷
	ARK_FF_SIT					= 0x0100,	// sit
	ARK_FF_BPE					= 0x0101,	// bpe
	ARK_FF_ACE					= 0x0102,	// ace
	ARK_FF_PAE					= 0x0104,	// PowerArchiver Encryption
	ARK_FF_XEF					= 0x0105,	// Winace Encryption
	ARK_FF_UNSUPPORTED_LAST		= 0x0105,

	ARK_FF_NOTARCHIVE_FIRST		= 0x0200,	// 명백히 압축파일이 아닌 파일 (실행파일, 이미지파일 등등..)
	ARK_FF_NULL					= 0x0201,	// 파일의 앞부분이 전부 0 으로 채워져 있는 파일
	ARK_FF_RIFF					= 0x0202,	// avi, wav
	ARK_FF_EXE					= 0x0203,	// sfx 가 아닌 일반 PE 실행파일
	ARK_FF_HTML					= 0x0204,	// HTML(정확하지는 않음)
	ARK_FF_JPG					= 0x0205,	// 
	ARK_FF_PNG					= 0x0206,	// 
	ARK_FF_GIF					= 0x0207,	// 
	ARK_FF_OGGS					= 0x0208,	// OggS
	ARK_FF_MATROSKA				= 0x0209,	// MKV
	ARK_FF_PDF					= 0x020a,	// PDF
	ARK_FF_NOTARCHIVE_LAST		= 0x020a,

};

// 암호화 방식
enum ARK_ENCRYPTION_METHOD
{
	ARK_ENCRYPTION_METHOD_NONE				= 0x00,
	ARK_ENCRYPTION_METHOD_ZIP				= 0x01,	// ZipCrypto
	ARK_ENCRYPTION_METHOD_AES128			= 0x02,	// zip
	ARK_ENCRYPTION_METHOD_AES192			= 0x03,	
	ARK_ENCRYPTION_METHOD_AES256			= 0x04,
											
	ARK_ENCRYPTION_METHOD_EGG_ZIP			= 0x05,	// EGG 포맷에서 사용
	ARK_ENCRYPTION_METHOD_EGG_AES128		= 0x06,
	ARK_ENCRYPTION_METHOD_EGG_AES256		= 0x07,

	ARK_ENCRYPTION_METHOD_RAR				= 0x08,	// RAR 암호 방식
	ARK_ENCRYPTION_METHOD_ACE				= 0x09,	// ACE 암호

	ARK_ENCRYPTION_METHOD_ETC				= 0x99,	

	ARK_ENCRYPTION_METHOD_NOTSUPPORTED_FIRST= 0x100,	// Not supported encryption method
	ARK_ENCRYPTION_METHOD_GARBLE,						// ARJ 암호 방식
	ARK_ENCRYPTION_METHOD_DES,
	ARK_ENCRYPTION_METHOD_RC2,
	ARK_ENCRYPTION_METHOD_3DES168,
	ARK_ENCRYPTION_METHOD_3DES112,
	ARK_ENCRYPTION_METHOD_PKAES128,
	ARK_ENCRYPTION_METHOD_PKAES192,
	ARK_ENCRYPTION_METHOD_PKAES256,
	ARK_ENCRYPTION_METHOD_RC2_2,
	ARK_ENCRYPTION_METHOD_BLOWFISH,
	ARK_ENCRYPTION_METHOD_TWOFISH,
	ARK_ENCRYPTION_METHOD_RC4,
	ARK_ENCRYPTION_METHOD_UNKNOWN,
};

// 압축 방식
enum ARK_COMPRESSION_METHOD
{
	/////////////////////////////////////////////////////////////////
	// zip 에서 사용하는것들, zip 포맷에 정의된 값과 동일하다.
	// (http://www.pkware.com/documents/casestudies/APPNOTE.TXT 참고)
	ARK_COMPRESSION_METHOD_STORE		=	0,
	ARK_COMPRESSION_METHOD_SHRINK		=	1,
	ARK_COMPRESSION_METHOD_IMPLODE		=	6,
	ARK_COMPRESSION_METHOD_DEFLATE		=	8,

	ARK_COMPRESSION_METHOD_DEFLATE64	=	9,
	ARK_COMPRESSION_METHOD_BZIP2		=	12,
	ARK_COMPRESSION_METHOD_LZMA			=	14,		// zipx, 7zip ...
	ARK_COMPRESSION_METHOD_JPEG			=	96,		// zipx
	ARK_COMPRESSION_METHOD_WAVPACK		=	97,		// zipx
	ARK_COMPRESSION_METHOD_PPMD			=	98,		// zipx, 7zip
	ARK_COMPRESSION_METHOD_AES			=	99,		// aes 로 암호화된 zip 파일. 실제 압축 방법은 다른곳에 저장된다.
	// 
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// ETC
	ARK_COMPRESSION_METHOD_FUSE			=	300,	// bh 에서 사용 
	ARK_COMPRESSION_METHOD_FUSE6		=	301,	// bh 에서 사용 
	ARK_COMPRESSION_METHOD_AZO			=	302,	// egg 에서 사용
	ARK_COMPRESSION_METHOD_COMPRESS		=	303,	// .Z 에서 사용

	ARK_COMPRESSION_METHOD_RAR15		=	400,	// RAR 1.5
	ARK_COMPRESSION_METHOD_RAR20		=	401,	// RAR 2.X
	ARK_COMPRESSION_METHOD_RAR26		=	402,	// RAR 2.X & 2GB 이상
	ARK_COMPRESSION_METHOD_RAR29		=	403,	// RAR 3.X
	ARK_COMPRESSION_METHOD_RAR36		=	404,	// RAR 3.X alternative hash

	ARK_COMPRESSION_METHOD_MSZIP		=	500,	// CAB
	ARK_COMPRESSION_METHOD_LHA			=	501,	// lzh
	ARK_COMPRESSION_METHOD_LZMA2		=	502,	// 7z
	ARK_COMPRESSION_METHOD_BCJ			=	503,	// 7z
	ARK_COMPRESSION_METHOD_BCJ2			=	504,	// 7z
	ARK_COMPRESSION_METHOD_LZX			=	505,	// CAB
	ARK_COMPRESSION_METHOD_LZXWIM		=	506,	// wim
	ARK_COMPRESSION_METHOD_OBDEFLATE	=	508,	// Obfuscated deflate (alz)
	ARK_COMPRESSION_METHOD_DELTA		=	509,	// 7z
	ARK_COMPRESSION_METHOD_XPRESS		=	510,	// wim - xpress

	ARK_COMPRESSION_METHOD_LH0			=	600,	// -lh0-
	ARK_COMPRESSION_METHOD_LH1			=	601,	// -lh1-
	ARK_COMPRESSION_METHOD_LH2			=	602,	// -lh2-
	ARK_COMPRESSION_METHOD_LH3			=	603,	// -lh3-
	ARK_COMPRESSION_METHOD_LH4			=	604,	// -lh4-
	ARK_COMPRESSION_METHOD_LH5			=	605,	// -lh5-
	ARK_COMPRESSION_METHOD_LH6			=	606,	// -lh6-
	ARK_COMPRESSION_METHOD_LH7			=	607,	// -lh7-
	ARK_COMPRESSION_METHOD_LZS			=	608,	// -lzs-
	ARK_COMPRESSION_METHOD_LZ5			=	609,	// -lz5-
	ARK_COMPRESSION_METHOD_LZ4			=	610,	// -lz4-
	ARK_COMPRESSION_METHOD_LHD			=	611,	// -lhd-
	ARK_COMPRESSION_METHOD_PM0			=	612,	// -pm0-
	ARK_COMPRESSION_METHOD_PM2			=	613,	// -pm2-

	ARK_COMPRESSION_METHOD_LZX15		=	715,	// LZX (WINDOW SIZE 15bit)
	ARK_COMPRESSION_METHOD_LZX16		=	716,	// 
	ARK_COMPRESSION_METHOD_LZX17		=	717,	// 
	ARK_COMPRESSION_METHOD_LZX18		=	718,	// 
	ARK_COMPRESSION_METHOD_LZX19		=	719,	// 
	ARK_COMPRESSION_METHOD_LZX20		=	720,	// 
	ARK_COMPRESSION_METHOD_LZX21		=	721,	// LZX (WINDOW SIZE 21bit)

	ARK_COMPRESSION_METHOD_QUANTUM10	=	810,	// QTMD(WINDOW SIZE 10bit)
	ARK_COMPRESSION_METHOD_QUANTUM11	=	811,	//
	ARK_COMPRESSION_METHOD_QUANTUM12	=	812,	//
	ARK_COMPRESSION_METHOD_QUANTUM13	=	813,	//
	ARK_COMPRESSION_METHOD_QUANTUM14	=	814,	//
	ARK_COMPRESSION_METHOD_QUANTUM15	=	815,	//
	ARK_COMPRESSION_METHOD_QUANTUM16	=	816,	//
	ARK_COMPRESSION_METHOD_QUANTUM17	=	817,	//
	ARK_COMPRESSION_METHOD_QUANTUM18	=	818,	//
	ARK_COMPRESSION_METHOD_QUANTUM19	=	819,	//
	ARK_COMPRESSION_METHOD_QUANTUM20	=	820,	//
	ARK_COMPRESSION_METHOD_QUANTUM21	=	821,	// QTMD(WINDOW SIZE 21bit)

	ARK_COMPRESSION_METHOD_ARJ1			=	901,	// Arj Method 1
	ARK_COMPRESSION_METHOD_ARJ2			=	902,	//            2
	ARK_COMPRESSION_METHOD_ARJ3			=	903,	//            3
	ARK_COMPRESSION_METHOD_ARJ4			=	904,	//            4

	ARK_COMPRESSION_METHOD_ACELZ77		=	910,	// ace lz77
	ARK_COMPRESSION_METHOD_ACE20		=	911,	// ace v20
	ARK_COMPRESSION_METHOD_ACE			=	912,	// ace 최신?

	// 
	/////////////////////////////////////////////////////////////////

	ARK_COMPRESSION_METHOD_UNKNOWN		=	9999,	// unknown
};

// 분할 압축 스타일
enum ARK_MULTIVOL_STYLE
{
	ARK_MULTIVOL_STYLE_NONE,			// 분할 압축파일이 아님
	ARK_MULTIVOL_STYLE_001,				// 7zip 의 001, 002, .. 스타일
	ARK_MULTIVOL_STYLE_WINZIP,			// winzip 스타일  (z01, z02 ..... zip)
	ARK_MULTIVOL_STYLE_ZIPX,			// winzip zipx 스타일  (zx01, zx02 ..... zipx)
	ARK_MULTIVOL_STYLE_ALZ,				// alzip 의 alz, a00, a01, a02, .. 스타일
	ARK_MULTIVOL_STYLE_EGG,				// vol1.egg vol2.egg vol3.egg ... 스타일
	ARK_MULTIVOL_STYLE_RAR,				// part1.rar part2.rar ... 스타일
	ARK_MULTIVOL_STYLE_R00,				// .rar .r00 .r01 스타일
	ARK_MULTIVOL_STYLE_ARJ,				// .arj .a01 .a02 스타일
	ARK_MULTIVOL_STYLE_BAMSFX,			// 밤톨이 sfx (exe, .002 .003 ...)
	ARK_MULTIVOL_STYLE_BDZSFX,			// 반디집 SFX (exe, .e01 .e02 ...)
	ARK_MULTIVOL_STYLE_CAB,				// 분할 cab 파일
};


// 파일 속성
#define ARK_FILEATTR					unsigned int
#define ARK_FILEATTR_NONE				0x00
#define ARK_FILEATTR_READONLY			0x01	// FILE_ATTRIBUTE_READONLY
#define ARK_FILEATTR_HIDDEN				0x02	// FILE_ATTRIBUTE_HIDDEN
#define ARK_FILEATTR_SYSTEM				0x04	// FILE_ATTRIBUTE_SYSTEM
#define ARK_FILEATTR_DIRECTORY			0x10	// FILE_ATTRIBUTE_DIRECTORY
#define ARK_FILEATTR_FILE				0x20	// FILE_ATTRIBUTE_ARCHIVE

// 코드 페이지
#define ARK_CP_ACP						0		// == CP_ACP
#define ARK_CP_OEM						1		// == CP_OEMCP
#define ARK_CP_KOR						949		// EUC-KR, CP949 
#define ARK_CP_JPN						932		// SHIFT-JIS, CP932
#define ARK_CP_UTF8						65001	// == CP_UTF8
#define ARK_CP_UTF8_MAC					65002	// 맥용 utf8 코드 페이지


// 기타 정의
#define ARK_FILESIZE_UNKNOWN			(0xffffffffffffffffLL)	// 파일 크기를 알 수 없을때 사용되는 값

// WIN32 이외의 시스템일 경우 기본 타입 정의
#ifndef TRUE
	#define FALSE               0
	#define TRUE                1
	typedef char				CHAR;
	typedef wchar_t				WCHAR;
	typedef unsigned int		UINT32;
	typedef const char*			LPCSTR;
	typedef const wchar_t*		LPCWSTR;
#endif

// BOOL 대신 BOOL32 를 사용한다.
typedef int				BOOL32;
typedef unsigned char   ARKBYTE;


#ifndef PURE
#	define PURE                = 0
#endif

#ifdef _WIN32
	typedef signed __int64      INT64;
	#define WINAPI				__stdcall
#else
	typedef signed long long	INT64;
	#define WINAPI				
	#define THREAD_PRIORITY_NORMAL 0
#endif

// use os default packing
#ifndef __APPLE__
#	pragma pack()
#endif

// 인터페이스 메써드 타입 정의
#define ARKMETHOD(type)	virtual type WINAPI

#define ARK_TIME_T			INT64					// time_t 와 동일
struct SArkFileTime									// FILETIME(ntfs)과 동일
{
	UINT32 dwLowDateTime;
	UINT32 dwHighDateTime;
};
struct SArkNtfsFileTimes							// NTSF 파일 시간 정보
{
	SArkFileTime	mtime;							// 마지막 수정 시간
	SArkFileTime	ctime;							// 파일을 생성한 시간
	SArkFileTime	atime;							// 마지막으로 파일에 접근한 시간
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일 아이템 정보
//
struct SArkFileItem
{
	CHAR*					fileName;					// 압축파일에 저장된 파일명 (이 이름은 폴더 경로명도 포함한다)
	WCHAR*					fileNameW;
	WCHAR*					fileCommentW;
	ARK_TIME_T				fileTime;					// last modified(write) time
	INT64					compressedSize;
	INT64					uncompressedSize;
	ARK_ENCRYPTION_METHOD	encryptionMethod;
	ARK_FILEATTR			attrib;
	UINT32					crc32;
	ARK_COMPRESSION_METHOD	compressionMethod;
	SArkNtfsFileTimes*		ntfsFileTimes;				// NTFS 파일 시간 정보. 압축파일에 NTFS 파일정보가 없으면 NULL임
	BOOL32					isUnicodeFileName;			// 유니코드를 지원하는 압축포맷을 통해서 가져온 파일 이름인가? (즉, fileNameW를 100% 믿을 수 있는가)

	BOOL32					IsFolder() const { return attrib & ARK_FILEATTR_DIRECTORY ? TRUE : FALSE;}
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축 및 압축 해제 진행 상황 정보
//
struct SArkProgressInfo
{
	float		fCurPercent;		// 현재 파일의 압축 해제 진행율(%)
	float		fTotPercent;		// 전체 파일의 압축 해제 진행율(%)
	BOOL32		bCompleting;		// 마무리 중인가?
	float		fCompletingPercent;	// 마무리 중일때 진행율(%)
	int			_processed;			// undocumented - do not use
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Ark 옵션 설정
//
struct SArkGlobalOpt
{
	SArkGlobalOpt()
	{
		bPrintAssert = TRUE;
		bTreatTGZAsSolidArchive = FALSE;
		bTreatTBZAsSolidArchive = FALSE;
		bAzoSupport = FALSE;
		bTreatUnixZipFileNameAsUTF8 = TRUE;
		bConvertNFD2NFCWhenMacOS = FALSE;
		bIgnoreMacOSXMetaFolder = FALSE;
		bUseLongPathName = FALSE;
		bOpenArchiveWithShareDelete = FALSE;
	}
	BOOL32 bPrintAssert;				// ASSERT 발생시 stdout 에 출력 여부 결정(posix 전용)
	BOOL32 bTreatTGZAsSolidArchive;		// TGZ 파일을 솔리드 압축된 파일처럼 처리하기
	BOOL32 bTreatTBZAsSolidArchive;		// TBZ 파일을 솔리드 압축된 파일처럼 처리하기
	BOOL32 bAzoSupport;					// azo 알고리즘 지원 여부
	BOOL32 bTreatUnixZipFileNameAsUTF8;	// zip 파일이 unix 에서 압축된 경우 무조건 utf8 코드페이지 처리
	BOOL32 bConvertNFD2NFCWhenMacOS;	// MAC OS 에서 압축한 파일일 경우 NFD를 NFC로 자동 변환
	BOOL32 bIgnoreMacOSXMetaFolder;		// zip 포맷의 __MACOSX/ 폴더를 무시한다.
	BOOL32 bUseLongPathName;			// 경로명이 260자가 넘어도 파일이나 폴더를 생성하기(Win32 전용)
	BOOL32 bOpenArchiveWithShareDelete;	// 압축파일 열때 FILE_SHARE_DELETE 속성으로 열기(Win32 전용)
};

// 코드페이지 관련
struct SArkDetectCodepage
{
	SArkDetectCodepage()
	{ fileCount2Detect=100; codePage = 0; codePageName[0] = 0; confidence=0; have2change=FALSE; }
	int		fileCount2Detect;			// [in] 앞에서 부터 몇개의 파일명을 가지고 처리할 것인가?
	int		codePage;					// [out] windows 용 codepage 숫자
	char	codePageName[128];			// [out] codepage 문자열 이름
	int		confidence;					// [out] 인식된 코드페이지의 신뢰도 (0~100)
	BOOL32	have2change;				// [out] 현재 코드페이지에 문제가 있는듯 하다. confidence 수치가 낮아도 바꾸는게 좋을듯.
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축 해제 진행 상황
//
enum ARK_OVERWRITE_MODE				// 파일 덮어쓰기 질문에 대한 사용자 대답
{
	ARK_OVERWRITE_MODE_OVERWRITE,
	ARK_OVERWRITE_MODE_SKIP, 
	ARK_OVERWRITE_MODE_RENAME,
};
enum ARK_PASSWORD_RET				// 파일 암호 질문에 대한 사용자 대답
{
	ARK_PASSWORD_RET_OK,
	ARK_PASSWORD_RET_CANCEL, 
};
enum ARK_PASSWORD_ASKTYPE			// OnAskPassword() 호출 이유
{
	ARK_PASSWORD_ASKTYPE_PASSWDNOTSET,	// 암호가 지정되지 않았음
	ARK_PASSWORD_ASKTYPE_INVALIDPASSWD,	// 기존에 지정된 암호가 틀렸음
};
#define ARK_MAX_PATH		300
#define ARK_MAX_PASS		300
struct IArkEvent
{
	ARKMETHOD(void)			OnOpening(const SArkFileItem* pFileItem, float progress, BOOL32& bStop) PURE;

	ARKMETHOD(void)			OnStartFile(const SArkFileItem* pFileItem, BOOL32& bStopCurrent, BOOL32& bStopAll, int index) PURE;
	ARKMETHOD(void)			OnProgressFile(const SArkProgressInfo* pProgressInfo, BOOL32& bStopCurrent, BOOL32& bStopAll) PURE;
	ARKMETHOD(void)			OnCompleteFile(const SArkProgressInfo* pProgressInfo, ARKERR nErr) PURE;

	ARKMETHOD(void)			OnError(ARKERR nErr, const SArkFileItem* pFileItem, BOOL32 bIsWarning, BOOL32& bStopAll) PURE;
	ARKMETHOD(void)			OnMultiVolumeFileChanged(LPCWSTR szPathFileName) PURE;

	ARKMETHOD(void)			OnAskOverwrite(const SArkFileItem* pFileItem, LPCWSTR szLocalPathName, ARK_OVERWRITE_MODE& overwrite, WCHAR pathName2Rename[ARK_MAX_PATH]) PURE;
	ARKMETHOD(void)			OnAskPassword(const SArkFileItem* pFileItem, ARK_PASSWORD_ASKTYPE askType, ARK_PASSWORD_RET& ret, WCHAR passwordW[ARK_MAX_PASS]) PURE;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축파일 출력 스트림
//
struct IArkSimpleOutStream
{
	ARKMETHOD(BOOL32)		Open(LPCWSTR szPathName) PURE;
	ARKMETHOD(BOOL32)		SetSize(INT64 nSize) PURE;
	ARKMETHOD(BOOL32)		Write(const void* lpBuffer, UINT32 nNumberOfBytesToWrite) PURE;
	ARKMETHOD(BOOL32)		Close() PURE;
	ARKMETHOD(BOOL32)		CreateFolder(LPCWSTR szPathName) PURE;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축파일 입력 스트림
//
struct IArkSimpleInStream
{
	ARKMETHOD(BOOL32)		Read(void* lpBuffer, UINT32 nNumberOfBytesToRead, UINT32* lpNumberOfBytesRead) PURE;
	ARKMETHOD(INT64)		SetPos(INT64 pos) PURE;
	ARKMETHOD(INT64)		GetPos() PURE;
	ARKMETHOD(INT64)		GetSize() PURE;
	ARKMETHOD(BOOL32)		Close() PURE;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MBCS 처리용 코드페이지
//
struct SArkCodepage
{
	SArkCodepage(){Init();}
	//SArkCodepage(int a, int b, int c, int d) {}
	void Init()
	{
		#ifdef _WIN32
		fileSystem = ARK_CP_ACP;
		#else
		fileSystem = ARK_CP_UTF8;	// POSIX 는 파일시스템에 보통 UTF8 코드페이지 사용
		#endif
		fileName = ARK_CP_OEM;
		comment = ARK_CP_ACP;
		password = ARK_CP_ACP;
	}
	int		fileSystem;				// 파일 시스템을 통해 압축파일을 열 때 사용하는 코드페이지. 보통 CP_ACP
	int		fileName;				// 압축파일 내부의 파일명을 처리할때 사용하는 코드페이지. 보통 CP_OEM
	int		comment;				// 압축파일 내부의 코멘트를 처리할때 사용하는 코드페이지. 보통 CP_ACP
	int		password;				// MBCS 암호를 처리할때 사용하는 코드페이지. 보통 CP_ACP
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축파일의 압축 해제 인터페이스
//
struct IArk
{
	ARKMETHOD(void)					Release() PURE;
									
	ARKMETHOD(BOOL32)  				Open(LPCSTR  filePath, LPCSTR password) PURE; 
	ARKMETHOD(BOOL32)  				Open(LPCWSTR filePath, LPCWSTR password) PURE; 
	ARKMETHOD(BOOL32)				Open(ARKBYTE* src, int srcLen, LPCWSTR password) PURE;
	ARKMETHOD(BOOL32)  				Open(IArkSimpleInStream* srcStream, LPCWSTR password) PURE; 
	ARKMETHOD(void)					Close() PURE;
	ARKMETHOD(BOOL32)  				TestArchive() PURE; 

	ARKMETHOD(ARK_FF)  				CheckFormat(LPCSTR  filePath) const PURE; 
	ARKMETHOD(ARK_FF)  				CheckFormat(LPCWSTR filePath) const PURE; 
	ARKMETHOD(ARK_FF)  				CheckFormat(const unsigned char* buffer, int bufLen) const PURE; 

	ARKMETHOD(void)					SetPassword(LPCSTR password) PURE;
	ARKMETHOD(void)					SetPassword(LPCWSTR password) PURE;
	ARKMETHOD(int)					GetFileItemCount() const PURE;
	ARKMETHOD(const SArkFileItem*)	GetFileItem(int index) const PURE;
	ARKMETHOD(ARK_FF)				GetFileFormat() const PURE;
	ARKMETHOD(BOOL32)				IsBrokenArchive() const PURE;
	ARKMETHOD(BOOL32)				IsEncryptedArchive() const PURE;
	ARKMETHOD(BOOL32)				IsSolidArchive() const PURE;
	ARKMETHOD(BOOL32)				IsOpened() const PURE;

	ARKMETHOD(BOOL32)				ExtractAllTo(LPCSTR folderPath) PURE;						// 전체 파일 풀기
	ARKMETHOD(BOOL32)				ExtractAllTo(LPCWSTR folderPath) PURE;
	ARKMETHOD(BOOL32)				ExtractAllTo(IArkSimpleOutStream* outStream) PURE;

	ARKMETHOD(BOOL32)				ExtractOneTo(int index, LPCWSTR folderPath) PURE;			// 하나 파일 풀기
	ARKMETHOD(BOOL32)				ExtractOneTo(int index, LPCSTR folderPath) PURE;
	ARKMETHOD(BOOL32)				ExtractOneTo(int index, IArkSimpleOutStream* outStream) PURE;
	ARKMETHOD(BOOL32)				ExtractOneTo(int index, ARKBYTE* outBuf, int outBufLen) PURE;
	ARKMETHOD(BOOL32)				ExtractOneAs(int index, LPCWSTR filePathName, WCHAR resultPathName[ARK_MAX_PATH]) PURE;			// 파일명을 지정해서 파일 하나 풀기

	ARKMETHOD(BOOL32)				AddIndex2ExtractList(int index) PURE;						// 압축풀 파일 인덱스를 목록에 추가
	ARKMETHOD(void)					ClearExtractList() PURE;									// 압축풀 파일 목록 삭제하기
	ARKMETHOD(int)					GetExtractListCount() const PURE;							// 압축풀 파일 목록의 갯수
	ARKMETHOD(BOOL32)				ExtractMultiFileTo(LPCSTR szDestPath) PURE;					// 몇개 파일 풀기
	ARKMETHOD(BOOL32)				ExtractMultiFileTo(LPCWSTR szDestPath, LPCWSTR szPath2Remove=NULL) PURE;
	ARKMETHOD(BOOL32)				ExtractMultiFileTo(IArkSimpleOutStream* outStream) PURE;

	ARKMETHOD(BOOL32)				SetEvent(IArkEvent* pEvent) PURE;
	ARKMETHOD(ARKERR)				GetLastError() const PURE;
	ARKMETHOD(UINT32)				GetLastSystemError() const PURE;
	ARKMETHOD(void)					SetCodePage(SArkCodepage cp) PURE;

	ARKMETHOD(LPCWSTR)				EncryptionMethod2Str(ARK_ENCRYPTION_METHOD method) const PURE;
	ARKMETHOD(LPCWSTR)				CompressionMethod2Str(ARK_COMPRESSION_METHOD method) const PURE;
	ARKMETHOD(LPCWSTR)				FileFormat2Str(ARK_FF ff) const PURE;

	ARKMETHOD(void)					SetGlobalOpt(const SArkGlobalOpt& opt) PURE;
	ARKMETHOD(INT64)				GetArchiveFileSize() const PURE;
	ARKMETHOD(INT64)				GetArchiveStartPos() const PURE;
	ARKMETHOD(LPCWSTR)				GetFilePathName() const PURE;
	ARKMETHOD(int)					FindIndex(LPCWSTR szFileNameW, LPCSTR szFileNameA, BOOL32 bCaseSensitive) const PURE;
	ARKMETHOD(LPCWSTR)				GetArchiveComment() const PURE;

	ARKMETHOD(ARK_MULTIVOL_STYLE)	GetMultivolStyle() const PURE;
	ARKMETHOD(int)					GetMultivolCount() const PURE;
	ARKMETHOD(LPCWSTR)				GetMultivolFilePathName(int volume) const PURE;

	ARKMETHOD(BOOL32)				DetectCurrentArchivesCodepage(SArkDetectCodepage& dcp) const PURE;
	ARKMETHOD(BOOL32)				ChangeCurrentArchivesCodepage(int codePage) PURE;


	///////////////////////
	// undocumented (do not use)
	ARKMETHOD(void)					_Test() PURE;
	ARKMETHOD(const void*)			_GetBondFileInfo() PURE;
	ARKMETHOD(LPCWSTR)				_GetAlias() PURE;
	ARKMETHOD(void)					_SetAlias(LPCWSTR szAlias) PURE;
	ARKMETHOD(void)					_SetUserKey(void* key) PURE;
	ARKMETHOD(UINT32)  				_CheckCRC32(LPCWSTR filePath) PURE; 
	ARKMETHOD(void*)				_GetExtractor() PURE;
	ARKMETHOD(void*)				_GetInStream() PURE;
	ARKMETHOD(BOOL32)				_DisableItem(int index) PURE;

	// for c++ builder
	ARKMETHOD(BOOL32)  				_OpenW(LPCWSTR filePath, LPCWSTR password) PURE; 
	ARKMETHOD(ARK_FF)  				_CheckFormatW(LPCWSTR filePath) const PURE; 
	ARKMETHOD(void)					_SetPasswordW(LPCWSTR password) PURE;
	ARKMETHOD(BOOL32)				_ExtractAllToW(LPCWSTR folderPath) PURE;
	ARKMETHOD(BOOL32)				_ExtractOneToW(int index, LPCWSTR folderPath) PURE;
	ARKMETHOD(BOOL32)				_ExtractMultiFileToW(LPCWSTR szDestPath, LPCWSTR szPath2Remove=NULL) PURE;
};


/////////////////////////////////////////////////////////
//
// 압축 옵션
//
struct SArkCompressorOpt
{
	SArkCompressorOpt(){Init();}
	void Init()
	{
		ff = ARK_FF_ZIP;
		saveNTFSTime = FALSE;
		streamOutput = FALSE;
		compressionMethod = ARK_COMPRESSION_METHOD_DEFLATE;
		encryptionMethod = ARK_ENCRYPTION_METHOD_ZIP;
		compressionLevel = -1;							// -1 은 Z_DEFAULT_COMPRESSION
		splitSize = 0;
		forceZip64 = FALSE;
		useDosTime2PasswordCheck = TRUE;
		sfxPathName = NULL;
		forceUtf8FileName = FALSE;
		forceUtf8Comment = FALSE;
		utf8FileNameIfNeeded = TRUE;
		bypassWhenUncompressible = FALSE;
		lzmaEncodeThreadCount = 2;
		enableMultithreadDeflate = FALSE;
		deflateEncodeThreadCount = 0;
		_7zCompressHeader = TRUE;
		_7zEncryptHeader = FALSE;
		lzma2NumBlockThreads = -1;
		threadPriority = THREAD_PRIORITY_NORMAL;
		deleteArchiveWhenFailed = TRUE;
	}
	ARK_FF					ff;							// 파일 포맷 ARK_FF_ZIP, ARK_FF_TAR, ARK_FF_TGZ, ARK_FF_7Z, ARK_FF_LZH, ARK_FF_ISO
	BOOL32					saveNTFSTime;				// ntfs 시간 저장 여부
	BOOL32					streamOutput;				// stream 형태로 저장 - 이 값이 TRUE 일 경우 열지 못하는 프로그램이 너무 많음.
	ARK_COMPRESSION_METHOD	compressionMethod;			// 압축 방식 ( ARK_COMPRESSION_METHOD_STORE, ARK_COMPRESSION_METHOD_DEFLATE, ARK_COMPRESSION_METHOD_LZMA )
	ARK_ENCRYPTION_METHOD	encryptionMethod;			// 파일에 암호를 걸 경우 사용할 암호 방식 ( ARK_ENCRYPTION_METHOD_ZIP, ARK_ENCRYPTION_METHOD_AES256 만 유효)
	int						compressionLevel;			// 압축 레벨 ( Z_NO_COMPRESSION, Z_BEST_SPEED ~ Z_BEST_COMPRESSION )
	INT64					splitSize;					// 분할 압축 크기 (bytes,  0 이면 분할 압축 안함)
	BOOL32					forceZip64;					// 강제로 zip64 정보 저장
	BOOL32					useDosTime2PasswordCheck;	// 암호 체크 데이타를 crc 대신 dostime 을 사용한다. (사용시 압축 속도 향상). 단 분할압축시 이 옵션은 무시됨
	LPCWSTR					sfxPathName;				// sfx를 만들경우 sfx 파일경로명. NULL 이면 사용하지 않음.
	BOOL32					forceUtf8FileName;			// 파일명을 모두 utf8 로 저장
	BOOL32					forceUtf8Comment;			// 압축파일 설명을 utf8 로 저장 (다른 프로그램과 호완되지 않음)
	BOOL32					utf8FileNameIfNeeded;		// 파일명에 유니코드가 포함되어 있을 경우 utf8 로 저장
	BOOL32					bypassWhenUncompressible;	// 압축중 압축이 안될경우 그냥 bypass
	int						lzmaEncodeThreadCount;		// LZMA 압축시 쓰레드 카운트. 1~2
	BOOL32					enableMultithreadDeflate;	// Deflate 압축시 멀티쓰레드 사용
	int						deflateEncodeThreadCount;	// Deflate 압축시 사용할 쓰래드 갯수. 0 이면 기본값 사용
	BOOL32					deleteArchiveWhenFailed;	// 압축중 에러 발생시 생성된 파일 삭제하기

	BOOL32					_7zCompressHeader;			// 7zip 압축시 헤더를 압축할 것인가?
	BOOL32					_7zEncryptHeader;			// 7zip 압축시 헤더를 암호화 할 것인가? (암호 지정시)
	int						lzma2NumBlockThreads;		// lzma2 압축시 쓰레드 갯수, -1 이면 시스템 갯수만큼
	int						threadPriority;				// 멀티코어를 이용해서 압축시 쓰레드 우선 순위
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 압축파일 만들기 인터페이스
//
struct IArkCompressor
{
	ARKMETHOD(void)			Release() PURE;												// 객체 해제

	ARKMETHOD(void)			Init() PURE;												// 초기화 (새로운 압축파일 생성 시작)
	ARKMETHOD(void)			SetEvent(IArkEvent* pEvent) PURE;							// 반드시 Init() 호출후 매번 호출해야 한다.
	ARKMETHOD(BOOL32)		SetOption(SArkCompressorOpt& opt, const ARKBYTE* password, int pwLen) PURE;// CreateArchive() 호출전에만 호출하면 언제 호출해도 상관없고, 한번 호출하면 끝

	ARKMETHOD(BOOL32)		SetArchiveFile(IArk* pArchive) PURE;						// 원본 파일 세팅 
	ARKMETHOD(BOOL32)		AddFileItem(LPCWSTR	szSrcPathName, LPCWSTR szTargetPathName, BOOL32 overwrite, LPCWSTR szFileComment=NULL, INT64 fileSize=-1) PURE;

	ARKMETHOD(BOOL32)		RenameItem(int index, LPCWSTR szPathName) PURE;				// SetArchiveFile() 로 지정한 파일의 이름을 바꾼다.
	ARKMETHOD(BOOL32)		DeleteItem(int index) PURE;									// SetArchiveFile() 로 지정한 파일을 삭제한다.

	ARKMETHOD(int)			FindFileItemIndex2Add(LPCWSTR szTargetPathName) PURE;						// 기존 목록에 존재하는지 확인한다.
	ARKMETHOD(BOOL32)		GetFileItemInfo(int index, INT64& fileSize, ARK_TIME_T& fileTime) PURE;		// 목록에 있는 파일의 정보 가져오기
	ARKMETHOD(INT64)		GetTotalFileSize2Archive() PURE;

	ARKMETHOD(BOOL32)		CreateArchive(LPCWSTR szPathName, LPCWSTR szArchiveComment=NULL) PURE;

	ARKMETHOD(ARKERR)		GetLastError() const PURE;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IArk, IArkCompressor 객체를 생성합니다. SDKVersion 파라메터는 ARK_LIBRARY_VERSION 을 넘기면 됩니다.
//

#ifdef _WIN32
extern "C" __declspec(dllexport) IArk*				CreateArk(UINT32 SDKVersion);
extern "C" __declspec(dllexport) IArkCompressor*	CreateArkCompressor(UINT32 SDKVersion);
#endif
extern "C" IArk*									CreateArkLib(UINT32 SDKVersion);


#endif // _ARK_H_
