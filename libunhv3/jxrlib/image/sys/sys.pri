
INCLUDEPATH *= $$PWD

HEADERS  += \
	$$PWD/ansi.h \
	$$PWD/common.h \
	$$PWD/perfTimer.h \
	$$PWD/strTransform.h \
	$$PWD/strcodec.h \
	$$PWD/windowsmediaphoto.h \
	$$PWD/xplatform_image.h

SOURCES  += \
	$$PWD/adapthuff.c \
	$$PWD/image.c \
	$$PWD/perfTimerANSI.c \
	$$PWD/strPredQuant.c \
	$$PWD/strTransform.c \
	$$PWD/strcodec.c
