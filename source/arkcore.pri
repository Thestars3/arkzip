# arkcore에 의존하는 프로그램에 대한 공통된 설정.

INCLUDEPATH += ../arkcore
DEPENDPATH += ../arkcore

LIBS += -L../arkcore/Release -l:libarkcore.so
