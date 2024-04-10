#-------------------------------------------------
#
# QtHelper sample
#
#-------------------------------------------------

QT       += core gui webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sample
TEMPLATE = app

SOURCES  += main.cpp\
            mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include($$PWD/../qt-helper.pri)
