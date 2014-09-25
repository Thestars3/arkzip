/*Copyright (C) 2014  별님

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef CARKEVENT_HPP
#define CARKEVENT_HPP

#include "ArkLibrary.hpp"
#include <QObject>
#include <functional>
#include "decompress.hpp"

/** 압축 해제 이벤트를 처리합니다.
  */
class CArkEvent :
        public QObject,
        public IArkEvent
{
    Q_OBJECT

public:
    explicit CArkEvent(QObject *parent = 0);
    void setSkipAskPassword(bool);

    // < -- IArkEvent 인터페이스 구현 -- >
    ARKMETHOD(void)	OnOpening(const SArkFileItem *pFileItem, float progress, BOOL32 &bStop);
    ARKMETHOD(void) OnStartFile(const SArkFileItem *pFileItem, BOOL32 &bStopCurrent, BOOL32 &bStopAll, int index);
    ARKMETHOD(void)	OnProgressFile(const SArkProgressInfo *pProgressInfo, BOOL32 &bStopCurrent, BOOL32 &bStopAll);
    ARKMETHOD(void)	OnCompleteFile(const SArkProgressInfo *pProgressInfo, ARKERR nErr);
    ARKMETHOD(void)	OnError(ARKERR nErr, const SArkFileItem *pFileItem, BOOL32 bIsWarning, BOOL32 &bStopAll);
    ARKMETHOD(void)	OnAskOverwrite(const SArkFileItem *pFileItem, LPCWSTR szLocalPathName, ARK_OVERWRITE_MODE &overwrite, WCHAR pathName2Rename[ARK_MAX_PATH]);
    ARKMETHOD(void)	OnAskPassword(const SArkFileItem *pFileItem, ARK_PASSWORD_ASKTYPE askType, ARK_PASSWORD_RET &ret, WCHAR passwordW[ARK_MAX_PASS]);
    ARKMETHOD(void)	OnMultiVolumeFileChanged(LPCWSTR szPathFileName); // 사용 안함.

private:
    Decompress *decompress;                 ///< Decompress 객체.
    std::function<QString()> getPassword;   ///< 암호 얻기 작업 수행시의 작업

    /** @brief 문자열을 지정된 배열로 복사합니다.
      wcsncpy 함수는 제한된 길이만큼 문자를 대상으로 복사하지만, 문자열의 끝을 설정해주지는 않는다.\n
      Ark 라이브러리에서는 내부적으로 wide charter를 UCS-4 인코딩으로 처리하고 있으므로, 다음과 같이 끝의 문자열을 \\0로 지정함으로서 문자열임을 보장할수 있다.\n
      Ark 라이브러리에서 내부적으로 해당 배열을 어떤식으로 처리하는지는 알 수 없으므로 다음과 같은 예방 작업을 시행해준다.\n
      */
    static inline void copy(
            WCHAR *to,         ///< 복사될 배열 포인터
            int toSize,        ///< 복사될 배열의 최대 크기
            QString from       ///< 복사할 문자열
            )
    {
        wcsncpy(to, from.toStdWString().c_str(), toSize);
        to[ toSize - 1 ] = L'\0';
    }

};

#endif // CARKEVENT_HPP
