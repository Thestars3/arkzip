# 프로그램 공통 설정.

# 공통된 컴파일 설정.
MOC_DIR = moc
UI_DIR = uic
CONFIG(debug, debug|release) {
	DEFINES += DEBUG
	DESTDIR = Debug
	OBJECTS_DIR = Debug
	buildTypeName = Debug
} else {
	DEFINES += QT_NO_DEBUG_OUTPUT
	DESTDIR = Release
	OBJECTS_DIR = Release
	buildTypeName = Release
}

#프로젝트 디렉토리
ROOT_PATH = $$system(readlink -f ..)
PROJECT_DIR_PATH = $$ROOT_PATH/source

# ArkLibrary 소스 폴더를 지정.
ARK_LIBRARY_DIR = $$ROOT_PATH/ArkLibrary

#테스트용
contains(buildMode, test) {
	message(테스트용으로 빌드합니다.)

	# ArkLibrary 경로를 설정.
	ARK_LIBRARY_PATH = $$ARK_LIBRARY_DIR/ArkLibrary64.so

	# arkcui 프로그램 경로
	ARK_CUI_PROGRAM_PATH = $$PROJECT_DIR_PATH/arkcui/$$buildTypeName/arkcui

	# arkgui 프로그램 경로
	ARK_GUI_PROGRAM_PATH = $$PROJECT_DIR_PATH/arkgui/$$buildTypeName/arkgui
	
	# arkcore 라이브러리 경로
	ARK_CORE_LIBRARY_PATH = $$PROJECT_DIR_PATH/arkcore/$$buildTypeName
	
#기본
} else {
	# ArkLibrary 경로를 설정.
	ARK_LIBRARY_PATH = /usr/lib/arkzip/ArkLibrary/ArkLibrary64.so

	# arkcui 프로그램 경로
	ARK_CUI_PROGRAM_PATH = /usr/share/arkzip/arkcui

	# arkgui 프로그램 경로
	ARK_GUI_PROGRAM_PATH = /usr/share/arkzip/arkgui

	# 프로그램 아이콘 경로
	ARKZIP_PROGRAM_ICON = /usr/share/arkzip/arkzip.svg
}
