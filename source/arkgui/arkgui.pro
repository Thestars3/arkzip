
include( ../common.pri )

TEMPLATE = app

CONFIG   -= app_bundle

QT       += core gui

TARGET = arkgui

SOURCES += \
	main.cpp\
	ui/trayicon.cpp \
	reportgui.cpp \
	decompressgui.cpp \
    ui/decompressprogresswidget.cpp

HEADERS += \
	ui/trayicon.hpp \
	reportgui.hpp \
	decompressgui.hpp \
    ui/decompressprogresswidget.hpp

FORMS += \
    ui/DecompressProgressWidget.ui

QMAKE_CXXFLAGS += -std=c++0x

LIBS += -l:libboost_program_options-mt.a

include( ../arkcore.pri )
