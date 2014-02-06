cache()

debug:CONFIG_NAME=Debug
release:CONFIG_NAME=Release

DEPS_PATH   = /Users/Franck/wk/cpp/deps
DEPS_INCLUDE= $$DEPS_PATH/include
QT_PATH     = $$DEPS_PATH/Qt

TEMPLATE = lib
QT = core gui webkit
CONFIG += staticlib

TARGET  = htmlgrab
DESTDIR = ../build/$$CONFIG_NAME
SOURCES+= src/*.cpp

HEADERS+= include/htmlgrab/jsClock.h

INCLUDEPATH+= $$DEPS_INCLUDE
INCLUDEPATH+= ./include

UI_DIR     = ./.tmp/$$CONFIG_NAME
MOC_DIR    = ./.tmp/$$CONFIG_NAME
RCC_DIR    = ./.tmp/$$CONFIG_NAME
OBJECTS_DIR= ./.tmp/$$CONFIG_NAME

