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

#ifndef UNHV3EVENT_HPP
#define UNHV3EVENT_HPP

#include "unhv3status.hpp"

class IArkEvent;

class Unhv3Event
{
private:
    IArkEvent *event_; ///< 이벤트 처리 객체 포인터

public:
    Unhv3Event();
    void setEvent(IArkEvent *event);

    // < -- 이벤트 -- >
    void setOpen();
    void setStartFile(const QString &filePath);
    void setError(const QString &filePathName, const Unhv3Status &status);
    void setProgress(float progress);
    void setComplete();
    QString convertDuplicatedName(const QString &filePath);

};

#endif // UNHV3EVENT_HPP
