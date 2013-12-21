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
        model/Client.cpp \
        model/Equipement.cpp \
        model/Pin.cpp \
        app/QEquipmentView.cpp \
        app/qequipementitem.cpp

HEADERS  += mainwindow.h\
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
        model/Client.h \
        model/Equipement.h \
        model/Pin.h \
        app/QEquipmentView.h \
        app/qequipementitem.h

FORMS    += mainwindow.ui \
    arduino_server_choice.ui \
    newequipementdialog.ui

RESOURCES += \
    resource.qrc





