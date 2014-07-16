
include( ../common.pri )

QT       -= gui

TARGET = arkcore
TEMPLATE = lib

VERSION = 1.0.0 #arkcore 라이브러리의 버전은 의미가 없습니다.

SOURCES += pause.cpp \
	report.cpp \
	carkevent.cpp \
	decompress.cpp \
	ufp/ufp.cpp \
	ufp/failmakedirexception.cpp \
    arkerrconverter.cpp

HEADERS += pause.hpp \
	report.hpp \
	carkevent.hpp \
	decompress.hpp \
	ufp/ufp.hpp \
	ufp/failmakedirexception.hpp \
    arkerrconverter.hpp

INCLUDEPATH += ../../ArkLibrary
DEPENDPATH += ../../ArkLibrary

DEFINES += \
	_FILE_OFFSET_BITS=64 \
	_LARGEFILE_SOURCE \
	DF_AA58F9E2C6BF94D18A1FE812398CE2233=\\\"$$join(ARK_LIBRARY_PATH, \\\x20)\\\"

QMAKE_CXXFLAGS += -std=c++0x

LIBS += -ldl -lboost_program_options
