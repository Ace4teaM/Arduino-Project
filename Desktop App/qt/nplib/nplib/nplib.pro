#-------------------------------------------------
#
# Project created by QtCreator 2013-12-23T17:44:35
#
#-------------------------------------------------

QT       -= gui

TARGET = nplib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += nplib.cpp \
    ../../../../../nplib/src/l1/endian.cpp \
    ../../../../../nplib/src/l1/memory.cpp \
    ../../../../../nplib/src/l1/result.cpp \
    ../../../../../nplib/src/l1/riff.cpp \
    ../../../../../nplib/src/l1/str.cpp \
    ../../../../../nplib/src/l1/xarg.cpp \
    ../../../../../nplib/src/l1/stdlib/fendian.cpp \
    ../../../../../nplib/src/l1/stdlib/friff.cpp

HEADERS += nplib.h \
    ../../../../../nplib/src/l1/endian.h \
    ../../../../../nplib/src/l1/memory.h \
    ../../../../../nplib/src/l1/result.h \
    ../../../../../nplib/src/l1/riff.h \
    ../../../../../nplib/src/l1/str.h \
    ../../../../../nplib/src/l1/xarg.h \
    ../../../../../nplib/src/l1/stdlib/fendian.h \
    ../../../../../nplib/src/l1/stdlib/friff.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
