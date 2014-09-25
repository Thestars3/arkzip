#-------------------------------------------------
#
# arkzip cui/none 인터페이스용 어플리케이션 프로젝트
#
#-------------------------------------------------

include( ../common.pri )

include( $$PROJECT_DIR_PATH/arkcore/arkcore_include.pri )

include( report/report.pri )

TEMPLATE = app

TARGET   = arkcui

QT       += core

QT       -= gui

CONFIG   += console

CONFIG   -= app_bundle

HEADERS  += \
	decompresscui.hpp

SOURCES  += \
	main.cpp \
    decompresscui.cpp
    
QMAKE_CXXFLAGS += -std=c++0x
