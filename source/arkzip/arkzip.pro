#-------------------------------------------------
#
# arkzip main 어플리케이션 프로젝트
#
#-------------------------------------------------

include( ../common.pri )

TEMPLATE = app

TARGET   = arkzip

QT       += core

QT       -= gui

CONFIG   += console

CONFIG   -= app_bundle

HEADERS  += \
	option.hpp \
	codepage/codepagegroup.hpp \
	codepage/codepagelist.hpp

SOURCES  += \
	main.cpp \
    option.cpp \
	codepage/codepagegroup.cpp \
	codepage/codepagelist.cpp

LIBS     += \
	-l:libboost_program_options-mt.a

DEFINES  += \
	DF_020C2DC2A183E03DEBCECB21F1B1DB380=\\\"$$join(ARK_CUI_PROGRAM_PATH, \\\\x20)\\\" \
	DF_48887DE835299C0AD335491A223436213=\\\"$$join(ARK_GUI_PROGRAM_PATH, \\\\x20)\\\"

QMAKE_CXXFLAGS += -std=c++0x
