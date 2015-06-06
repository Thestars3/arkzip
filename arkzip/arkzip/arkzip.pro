#-------------------------------------------------
#
# arkzip main 어플리케이션 프로젝트
#
#-------------------------------------------------

include( ../common.pri )
include( codepage/codepage.pri )

TEMPLATE = app
TARGET   = arkzip
QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
HEADERS  += \
	option.hpp 
SOURCES  += \
	main.cpp \
    option.cpp
LIBS     += \
	-l:libboost_program_options-mt.a
DEFINES  += \
	_ARK_CUI_PROGRAM_PATH="'\"$$ARK_CUI_PROGRAM_PATH\"'" \
	_ARK_GUI_PROGRAM_PATH="'\"$$ARK_GUI_PROGRAM_PATH\"'" \
	_ARKCORE_DIR_PATH="'\"$$PROJECT_DIR_PATH/arkcore/$$DESTDIR\"'" \
	_LIBUNHV3_DIR_PATH="'\"$$ROOT_PATH/libunhv3/libunhv3/$$DESTDIR\"'" \
	_ARKZIP_VERSION_INFO="'\"$$system(cat "'$${ROOT_PATH}/version'")\"'"
QMAKE_CXXFLAGS += -std=c++0x
