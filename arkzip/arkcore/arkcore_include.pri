#-------------------------------------------------
#
# arkcore에 의존하는 프로그램에 대한 공통된 설정.
#
#-------------------------------------------------

LIBS        += \
	-L'$$PWD/$$DESTDIR' -larkcore \
	-l:libboost_program_options-mt.a

INCLUDEPATH *= $$PWD

DEPENDPATH  *= $$PWD

include( $$ROOT_PATH/libunhv3/libunhv3_include.pri )
