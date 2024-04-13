#-------------------------------------------------
# QtHelper sample
#-------------------------------------------------

QT           += core gui network webkitwidgets webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES      += QT_DEPRECATED_WARNINGS

# disables all the APIs deprecated before Qt 6.0.0
DEFINES      += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES      += main.cpp\
                mainwindow.cpp

HEADERS      += mainwindow.h

FORMS        += mainwindow.ui

TRANSLATIONS += locales/en_US.ts

include($$PWD/../qt-helper.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
