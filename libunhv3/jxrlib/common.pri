#-------------------------------------------------
#
# 공통된 컴파일 설정.
#
#-------------------------------------------------

include( ../common.pri )

#소스 디렉토리
PROJECT_DIR_PATH = $$PWD

VERSION = 1.1

INCLUDEPATH  += \
	$${PROJECT_DIR_PATH}/common/include \
	$${PROJECT_DIR_PATH}/image/sys \
	$${PROJECT_DIR_PATH}/image/x86

DEFINES      += \
	__ANSI__ \
	DISABLE_PERF_MEASUREMENT

QMAKE_CFLAGS_WARN_ON += -w

QMAKE_CFLAGS_RELEASE += -O
