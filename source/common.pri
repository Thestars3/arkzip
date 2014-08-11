#-------------------------------------------------
#
# 공통된 컴파일 설정.
#
#-------------------------------------------------

#프로젝트 디렉토리
ROOT_PATH        = $$system(readlink -f ..)

#ArkLibrary 소스 폴더를 지정.
ARK_LIBRARY_DIR  = $$ROOT_PATH/ArkLibrary

#소스 디렉토리
PROJECT_DIR_PATH = $$ROOT_PATH/source

#Debug
CONFIG(debug, debug|release) {
	DEFINES += DEBUG

	DESTDIR = Debug

	# ArkLibrary 경로를 설정.
	ARK_LIBRARY_PATH     = $$ARK_LIBRARY_DIR/ArkLibrary64.so

	# arkcui 프로그램 경로
	ARK_CUI_PROGRAM_PATH = $$PROJECT_DIR_PATH/arkcui/$$DESTDIR/arkcui

	# arkgui 프로그램 경로
	ARK_GUI_PROGRAM_PATH = $$PROJECT_DIR_PATH/arkgui/$$DESTDIR/arkgui

#Release
} else {
	DEFINES += QT_NO_DEBUG_OUTPUT

	DESTDIR = Release

	# ArkLibrary 경로를 설정.
	ARK_LIBRARY_PATH     = /usr/lib/arkzip/ArkLibrary/ArkLibrary64.so

	# arkcui 프로그램 경로
	ARK_CUI_PROGRAM_PATH = /usr/share/arkzip/arkcui

	# arkgui 프로그램 경로
	ARK_GUI_PROGRAM_PATH = /usr/share/arkzip/arkgui
}

UI_DIR      = $$DESTDIR

MOC_DIR     = $$DESTDIR

OBJECTS_DIR = $$DESTDIR
