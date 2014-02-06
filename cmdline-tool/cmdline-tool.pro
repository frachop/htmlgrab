cache()

debug:CONFIG_NAME=Debug
release:CONFIG_NAME=Release

#DEPS_PATH   = /Users/Franck/wk/cpp/deps
DEPS_PATH   = /usr/lib/x86_64-linux-gnu
DEPS_INCLUDE= $$DEPS_PATH/include
#DEPS_LIB    = $$DEPS_PATH/lib
DEPS_LIB    = $$DEPS_PATH
QT_PATH     = $$DEPS_PATH/Qt

TEMPLATE = app
win32:TEMPLATE+=console

CONFIG+=qt
mac:CONFIG-=app_bundle

QT += widgets webkit webkitwidgets

TARGET  = htmlgrab
DESTDIR = ../build/$$CONFIG_NAME
SOURCES+= src/*.cpp

INCLUDEPATH+= $$DEPS_INCLUDE
INCLUDEPATH+= ../api/include

LIBS += $$DESTDIR/libhtmlgrab.a 
LIBS += $$DEPS_LIB/libboost_system.a 
LIBS += $$DEPS_LIB/libboost_program_options.a 

UI_DIR     = ./.tmp/$$CONFIG_NAME
MOC_DIR    = ./.tmp/$$CONFIG_NAME
RCC_DIR    = ./.tmp/$$CONFIG_NAME
OBJECTS_DIR= ./.tmp/$$CONFIG_NAME

