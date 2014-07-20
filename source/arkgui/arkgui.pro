#-------------------------------------------------
#
# arkzip gui 인터페이스용 어플리케이션 프로젝트
#
#-------------------------------------------------

include( ../common.pri )

include( ../arkcore.pri )

TEMPLATE = app

TARGET   = arkgui

QT       += core gui

CONFIG   -= app_bundle

HEADERS  += \
	ui/trayicon.hpp \
	reportgui.hpp \
	decompressgui.hpp \
	ui/decompressprogresswidget.hpp

SOURCES  += \
	main.cpp\
	ui/trayicon.cpp \
	reportgui.cpp \
	decompressgui.cpp \
    ui/decompressprogresswidget.cpp

FORMS    += \
    ui/DecompressProgressWidget.ui

QMAKE_CXXFLAGS += -std=c++0x
