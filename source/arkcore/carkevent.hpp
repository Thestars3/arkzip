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
#include "decompress.hpp"
#include <QObject>
#include <functional>

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

private:
    Decompress *decompress;                 ///< Decompress 객체.
    std::function<QString()> getPassword;   ///< 암호 얻기 작업 수행시의 작업

private:
    void copy(WCHAR *to, int toSize, QString from);

    //IArkEvent 인터페이스 구현
public:
    ARKMETHOD(void)	OnOpening(const SArkFileItem* pFileItem, float progress, BOOL32& bStop);
    ARKMETHOD(void)	OnMultiVolumeFileChanged(LPCWSTR szPathFileName);
    ARKMETHOD(void) OnStartFile(const SArkFileItem* pFileItem, BOOL32& bStopCurrent, BOOL32& bStopAll, int index);
    ARKMETHOD(void)	OnProgressFile(const SArkProgressInfo* pProgressInfo, BOOL32& bStopCurrent, BOOL32& bStopAll);
    ARKMETHOD(void)	OnCompleteFile(const SArkProgressInfo* pProgressInfo, ARKERR nErr);
    ARKMETHOD(void)	OnError(ARKERR nErr, const SArkFileItem* pFileItem, BOOL32 bIsWarning, BOOL32& bStopAll);
    ARKMETHOD(void)	OnAskOverwrite(const SArkFileItem* pFileItem, LPCWSTR szLocalPathName, ARK_OVERWRITE_MODE& overwrite, WCHAR pathName2Rename[ARK_MAX_PATH]);
    ARKMETHOD(void)	OnAskPassword(const SArkFileItem* pFileItem, ARK_PASSWORD_ASKTYPE askType, ARK_PASSWORD_RET& ret, WCHAR passwordW[ARK_MAX_PASS]);

};

#endif // CARKEVENT_HPP
