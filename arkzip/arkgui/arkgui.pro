#-------------------------------------------------
#
# arkzip gui 인터페이스용 어플리케이션 프로젝트
#
#-------------------------------------------------

include( ../common.pri )

include( $$PROJECT_DIR_PATH/arkcore/arkcore_include.pri )

include( ui/ui.pri )

TEMPLATE = app

TARGET   = arkgui

QT       += core gui

CONFIG   -= app_bundle

HEADERS  += \
	reportgui.hpp \
	decompressgui.hpp
	
SOURCES  += \
	main.cpp\
	reportgui.cpp \
	decompressgui.cpp

QMAKE_CXXFLAGS += -std=c++0x
