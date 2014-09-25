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

#ifndef HDPIMAGEIOHANDLER_HPP
#define HDPIMAGEIOHANDLER_HPP

#include <QImageIOHandler>

typedef long ERR;
typedef struct tagPKImageDecode PKImageDecode;
typedef struct tagPKImageEncode PKImageEncode;

class HdpImageIOHandler :
        public QImageIOHandler
{
public:
    virtual bool canRead() const;
    virtual bool read(QImage *outImage);

private:
    ERR PKCodecFactory_CreateDecoderFromMemory(PKImageDecode **ppDecoder);
    void writeImage(PKImageEncode *pEncoder, QImage *outImage);
    void convertRgbaToArgb(uchar *p, uint size);

    template<typename T> static inline T inchConvertToMeter(
            const T &inch ///< 인치 단위
            )
    {
        // inch * 5000 / 127 = meter
        return inch * ( 100 / 2.54 );
    }

};

#endif // HDPIMAGEIOHANDLER_HPP
