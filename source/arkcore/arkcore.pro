#-------------------------------------------------
#
# arkcore 정적 라이브러리 프로젝트
#
#-------------------------------------------------

include( ../common.pri )

TEMPLATE = lib

TARGET   = arkcore

QT       -= gui

CONFIG   += staticlib

HEADERS  += \
	pause.hpp \
	report.hpp \
	carkevent.hpp \
	decompress.hpp \
	ufp/ufp.hpp \
	ufp/failmakedirexception.hpp \
	arkerrconverter.hpp

SOURCES  += \
	pause.cpp \
	report.cpp \
	carkevent.cpp \
	decompress.cpp \
	ufp/ufp.cpp \
	ufp/failmakedirexception.cpp \
    arkerrconverter.cpp

DEFINES  += \
	_FILE_OFFSET_BITS=64 \
	_LARGEFILE_SOURCE \
	DF_AA58F9E2C6BF94D18A1FE812398CE2233=\\\"$$join(ARK_LIBRARY_PATH, \\\x20)\\\"

INCLUDEPATH += ../../ArkLibrary

DEPENDPATH  += ../../ArkLibrary

QMAKE_CXXFLAGS += -std=c++0x
