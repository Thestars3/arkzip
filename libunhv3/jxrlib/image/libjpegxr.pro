#-------------------------------------------------
#
# libjpegxr 프로젝트
#
#-------------------------------------------------

include( ../common.pri )

include( decode/decode.pri )

include( encode/encode.pri )

include( sys/sys.pri )

TEMPLATE = lib

TARGET   = jpegxr

QT       -= gui

CONFIG   += staticlib
