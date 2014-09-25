#ifndef EVENTINTERFACE_HPP
#define EVENTINTERFACE_HPP

#include <QtGlobal>
#include "arkerrconverter.hpp"

typedef int ARK_OVERWRITE_MODE;
typedef int ARK_COMPRESSION_METHOD;
typedef int ARK_ENCRYPTION_METHOD;
typedef int ARK_PASSWORD_ASKTYPE;
typedef int ARK_PASSWORD_RET;
typedef uint ARK_FILEATTR;
typedef qint64 INT64;
typedef qint32 BOOL32;
typedef quint32 UINT32;
typedef UINT32 ARK_TIME_T;
typedef wchar_t WCHAR;
typedef const wchar_t* LPCWSTR;
typedef char CHAR;
struct SArkNtfsFileTimes;

struct SArkProgressInfo {
    float   fCurPercent;
    float   fTotPercent;
    int     bCompleting;
    float   fCompletingPercent;
};

struct SArkFileItem {
    CHAR*                   fileName;
    WCHAR*                  fileNameW;
    WCHAR*                  fileCommentW;
    ARK_TIME_T              fileTime;
    INT64                   compressedSize;
    INT64                   uncompressedSize;
    ARK_ENCRYPTION_METHOD   encryptionMethod;
    ARK_FILEATTR            attrib;
    UINT32                  crc32;
    ARK_COMPRESSION_METHOD  compressionMethod;
    SArkNtfsFileTimes*      ntfsFileTimes;
    BOOL32                  isUnicodeFileName;
};

#define ARK_MAX_PATH		300
#define ARK_MAX_PASS		300

class IArkEvent
{
public:
    virtual void OnOpening(const SArkFileItem* pFileItem, float progress, BOOL32& bStop) = 0;

    virtual void OnStartFile(const SArkFileItem* pFileItem, BOOL32& bStopCurrent, BOOL32& bStopAll, int index) = 0;
    virtual void OnProgressFile(const SArkProgressInfo* pProgressInfo, BOOL32& bStopCurrent, BOOL32& bStopAll) = 0;
    virtual void OnCompleteFile(const SArkProgressInfo* pProgressInfo, ARKERR nErr) = 0;

    virtual void OnError(ARKERR nErr, const SArkFileItem* pFileItem, BOOL32 bIsWarning, BOOL32& bStopAll) = 0;
    virtual void OnMultiVolumeFileChanged(LPCWSTR szPathFileName) = 0;

    virtual void OnAskOverwrite(const SArkFileItem* pFileItem, LPCWSTR szLocalPathName, ARK_OVERWRITE_MODE& overwrite, WCHAR pathName2Rename[ARK_MAX_PATH]) = 0;
    virtual void OnAskPassword(const SArkFileItem* pFileItem, ARK_PASSWORD_ASKTYPE askType, ARK_PASSWORD_RET& ret, WCHAR passwordW[ARK_MAX_PASS]) = 0;

};

#endif // EVENTINTERFACE_HPP
