#-------------------------------------------------
#
# Project created by QtCreator 2014-06-25T03:10:15
#
#-------------------------------------------------

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

LIBS += -lboost_program_options

include( ../arkcore.pri )
