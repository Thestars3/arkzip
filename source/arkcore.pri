#-------------------------------------------------
#
# arkcore에 의존하는 프로그램에 대한 공통된 설정.
#
#-------------------------------------------------

LIBS        += \
#	-ldl \ #ArkLibrary를 위해 포함시켜야 함. qt는 이미 포함되어 제외함.
	-L../arkcore/$$DESTDIR -l:libarkcore.a \
	-l:libboost_program_options-mt.a

DEPENDPATH  += ../arkcore

INCLUDEPATH += ../arkcore
