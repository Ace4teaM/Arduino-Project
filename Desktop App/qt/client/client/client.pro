#-------------------------------------------------
#
# Project created by QtCreator 2013-08-18T17:25:40
#
#-------------------------------------------------

QT       += core gui network sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app

# Ajoute les fonctions de debogage
Debug:DEFINES += _DEBUG

# Include pour la librairie NP
win32:INCLUDEPATH += "../../../../../nplib/src"

SOURCES += main.cpp\
        mainwindow.cpp \
        arduino_server_choice.cpp \
        newequipementdialog.cpp \
        app/result.cpp \
        app/configurable.cpp \
        app/application.cpp \
        app/qassoclist.cpp \
        app/database.cpp \
        app/qdelay.cpp \
        app/QEquipmentView.cpp \
        app/qequipmentitem.cpp \
        app/qequipmentscene.cpp \
        app/qserveritem.cpp \
        model/Server.cpp \
        model/Client.cpp \
        model/Equipment.cpp \
        model/LedControler.cpp \
        model/Switcher.cpp \
        equipprop_analogpin.cpp \
        equipprop_digitalpin.cpp \
        equipprop.cpp \
        equipdialog.cpp \
        equipmessagedialog.cpp

HEADERS  += mainwindow.h \
        result.h\
        xarg.h \
        arduino_server_choice.h \
        newequipementdialog.h \
        app/result.h \
        app/configurable.h \
        app/application.h \
        app/qassoclist.h \
        app/database.h \
        app/qdelay.h \
        app/iapplicationevent.h \
        app/QEquipmentView.h \
        app/qequipmentitem.h \
        app/qequipmentscene.h \
        app/qserveritem.h \
        model/Server.h \
        model/Client.h \
        model/Equipment.h \
        model/LedControler.h \
        model/Switcher.h \
        equipprop_analogpin.h \
        equipprop_digitalpin.h \
        equipprop.h \
        equipdialog.h \
        iequipprop.h \
        riff.h \
        equipmessagedialog.h \
        equip_types.h

FORMS    += mainwindow.ui \
    arduino_server_choice.ui \
    newequipementdialog.ui \
    equipprop_analogpin.ui \
    equipprop_digitalpin.ui \
    equipprop.ui \
    equipdialog.ui \
    equipmessagedialog.ui

RESOURCES += \
    resource.qrc



#nplib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../nplib/build-nplib-Desktop_Qt_5_2_0_MinGW_32bit-Debug/release/ -lnplib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../nplib/build-nplib-Desktop_Qt_5_2_0_MinGW_32bit-Debug/debug/ -lnplib
else:unix: LIBS += -L$$PWD/../../nplib/build-nplib-Desktop_Qt_5_2_0_MinGW_32bit-Debug/ -lnplib

INCLUDEPATH += $$PWD/../../nplib/build-nplib-Desktop_Qt_5_2_0_MinGW_32bit-Debug/debug
DEPENDPATH += $$PWD/../../nplib/build-nplib-Desktop_Qt_5_2_0_MinGW_32bit-Debug/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../nplib/build-nplib-Desktop_Qt_5_2_0_MinGW_32bit-Debug/release/libnplib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../nplib/build-nplib-Desktop_Qt_5_2_0_MinGW_32bit-Debug/debug/libnplib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../nplib/build-nplib-Desktop_Qt_5_2_0_MinGW_32bit-Debug/release/nplib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../nplib/build-nplib-Desktop_Qt_5_2_0_MinGW_32bit-Debug/debug/nplib.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../nplib/build-nplib-Desktop_Qt_5_2_0_MinGW_32bit-Debug/libnplib.a
