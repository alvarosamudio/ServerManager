#-------------------------------------------------
#
# Project created by QtCreator 2020-08-01T22:02:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

TRANSLATIONS += translations/servermanager_zh.ts \
                translations/servermanager_es.ts \
                translations/servermanager_pt.ts \
                translations/servermanager_it.ts \
                translations/servermanager_fr.ts
