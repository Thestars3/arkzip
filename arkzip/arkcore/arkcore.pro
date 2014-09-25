#-------------------------------------------------
#
# arkcore 라이브러리 프로젝트
#
#-------------------------------------------------

include( ../common.pri )

include( ufp/ufp.pri )

include( $$ARK_LIBRARY_DIR/ArkLibrary_include.pri )

include( $$ROOT_PATH/libunhv3/libunhv3_include.pri )

TEMPLATE = lib

TARGET   = arkcore

QT       -= gui

HEADERS  += \
	pause.hpp \
	report.hpp \
	carkevent.hpp \
	decompress.hpp \
	arkerrconverter.hpp \
    codeconv.hpp \
    arklib.hpp

SOURCES  += \
	pause.cpp \
	report.cpp \
	carkevent.cpp \
	decompress.cpp \
    arkerrconverter.cpp \
    codeconv.cpp \
    arklib.cpp

DEFINES  += \
	_FILE_OFFSET_BITS=64 \
	_LARGEFILE_SOURCE \
	_ARK_LIBRARY_PATH="'\"$$ARK_LIBRARY_PATH\"'"

QMAKE_CXXFLAGS += -std=c++0x
