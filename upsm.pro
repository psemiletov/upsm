#-------------------------------------------------
#
# Project created by QtCreator 2017-06-30T11:27:20
#
#-------------------------------------------------

VERSION=1.3.4
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RESOURCES += upsm.qrc


isEmpty(PREFIX) {
PREFIX = /usr/local
}


TARGET = bin/upsm
target.path = $$PREFIX/bin
desktop.path=$$PREFIX/share/applications
desktop.files=desktop/upsm.desktop

icon128.path = $$PREFIX/share/icons/hicolor/128x128/apps/
icon128.files += icons/upsm.png


TEMPLATE = app
TRANSLATIONS = ./translations/upsm_ru.ts

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += main.cpp\
           mainwindow.cpp

HEADERS  += mainwindow.h

DISTFILES += translations/* \
             desktop/* \
             icons/* \
             manuals/* \
             README \
             ChangeLog \
             CMakeLists.txt

INSTALLS += target desktop icon128
