#-------------------------------------------------
#
# libunhv3 가져오기 설정
#
#-------------------------------------------------

INCLUDEPATH *= \
	$$PWD/libunhv3 \
	$$PWD/libunhv3/unhv3 \
	$$PWD/libunhv3/bondchunk

#Debug
CONFIG(debug, debug|release) {
	DESTDIR = Debug

	DEFINES += _HDP_IMAGE_PLUGIN_PATH="'\"$$PWD/hdp_image_plugin/$$DESTDIR\"'"

#Release
} else {
	DESTDIR = Release
}
	
LIBS += \
	-L'$$PWD/libunhv3/$$DESTDIR' -lunhv3
