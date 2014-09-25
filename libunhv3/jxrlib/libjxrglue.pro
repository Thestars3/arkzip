#-------------------------------------------------
#
# libjxrglue 프로젝트
#
#-------------------------------------------------

include( common.pri )

include( jxrgluelib/jxrgluelib.pri )

include( jxrtestlib/jxrtestlib.pri )

TEMPLATE = lib

TARGET   = jxrglue

QT       -= gui

CONFIG   += staticlib
