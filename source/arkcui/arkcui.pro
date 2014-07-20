#-------------------------------------------------
#
# arkzip cui/none 인터페이스용 어플리케이션 프로젝트
#
#-------------------------------------------------

include( ../common.pri )

include( ../arkcore.pri )

TEMPLATE = app

TARGET   = arkcui

QT       += core

QT       -= gui

CONFIG   += console

CONFIG   -= app_bundle

HEADERS  += \
	report/reportinteractive.hpp \
	report/reportinteractivenoterminal.hpp \
	decompresscui.hpp

SOURCES  += \
	main.cpp \
	report/reportinteractive.cpp \
	report/reportinteractivenoterminal.cpp \
    decompresscui.cpp

QMAKE_CXXFLAGS += -std=c++0x
