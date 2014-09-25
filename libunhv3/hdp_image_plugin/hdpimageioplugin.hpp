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

#ifndef HDPIMAGEIOPLUGIN_HPP
#define HDPIMAGEIOPLUGIN_HPP

#include <QImageIOPlugin>

class HdpImageIOPlugin :
        public QImageIOPlugin
{
private:
    QStringList suportFormat; ///< 지원 포멧 리스트

public:
    HdpImageIOPlugin(QObject *parent = 0);
    virtual Capabilities capabilities(QIODevice *device, const QByteArray &format) const;
    virtual QImageIOHandler* create(QIODevice *device, const QByteArray &format = QByteArray()) const;
    virtual QStringList keys() const;

};

#endif // HDPIMAGEIOPLUGIN_HPP
