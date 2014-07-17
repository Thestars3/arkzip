
include( ../common.pri )

TEMPLATE = app

CONFIG   -= app_bundle

QT       += core

QT       -= gui

TARGET = arkcui
CONFIG   += console

SOURCES += main.cpp \
	report/reportinteractive.cpp \
	report/reportinteractivenoterminal.cpp \
    decompresscui.cpp

HEADERS += \
	report/reportinteractive.hpp \
	report/reportinteractivenoterminal.hpp \
    decompresscui.hpp

QMAKE_CXXFLAGS += -std=c++0x

LIBS += -l:libboost_program_options-mt.a

include( ../arkcore.pri )
