#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T11:19:11
#
#-------------------------------------------------

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
	DF_AA58F9E2C6BF94D18A1FE812398CE2233=\\\"$$join(ARK_LIBRARY_PATH, \\\x20)\\\"

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

LIBS += -ldl -lboost_program_options

QMAKE_CXXFLAGS += -fPIC -std=c++0x

DEFINES += \
	_FILE_OFFSET_BITS=64 \
	_LARGEFILE_SOURCE
