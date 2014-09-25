#-------------------------------------------------
#
# hdp QImageIOPlugin 프로젝트
#
#-------------------------------------------------

include( ../common.pri )

include( $$ROOT_PATH/jxrlib/jxrlib_include.pri )

TEMPLATE = lib

TARGET   = hdp_image

CONFIG   += plugin

HEADERS  += \
    hdpimageioplugin.hpp \
    hdpimageiohandler.hpp

SOURCES  += \
    hdpimageioplugin.cpp \
    hdpimageiohandler.cpp

QMAKE_CXXFLAGS += -std=c++0x

#Debug
CONFIG(debug, debug|release) {
	DESTDIR = $$DESTDIR/imageformats
}
