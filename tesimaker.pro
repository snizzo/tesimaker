#-------------------------------------------------
#
# Project created by QtCreator 2016-11-22T17:12:33
#
#-------------------------------------------------

QT       += core gui script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qscintilla2
TARGET = tesimaker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    simplelatexparser.cpp \
    languageelement.cpp \
    latextranslator.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    simplelatexparser.h \
    languageelement.h \
    latextranslator.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    common.qrc
