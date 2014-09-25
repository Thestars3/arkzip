#-------------------------------------------------
#
# 공통된 컴파일 설정.
#
#-------------------------------------------------

#프로젝트 디렉토리
ROOT_PATH   = $$PWD

#Debug
CONFIG(debug, debug|release) {
	DEFINES += DEBUG

	DESTDIR = Debug

#Release
} else {
	DEFINES += QT_NO_DEBUG_OUTPUT

	DESTDIR = Release
}

UI_DIR      = $$DESTDIR

MOC_DIR     = $$DESTDIR

OBJECTS_DIR = $$DESTDIR
