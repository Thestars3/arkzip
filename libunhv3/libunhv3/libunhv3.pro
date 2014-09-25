#-------------------------------------------------
#
# libunhv3 프로젝트
#
#-------------------------------------------------

include( ../common.pri )

include( bondchunk/bondchunk.pri )

include( unhv3/unhv3.pri )

TEMPLATE = lib

TARGET   = unhv3

QT       += gui

VERSION  = $$system(cat "'$${ROOT_PATH}/version'")

HEADERS  += \
    unhv3_global.hpp \
	ufp.hpp

SOURCES  += \
	ufp.cpp

DEFINES  += UNHV3_LIBRARY

QMAKE_CXXFLAGS += -std=c++0x
