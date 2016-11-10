qt-helper
=========

Simple Qt library to improve and help in their projects

Usage:
-----

For use all classes add in your project something like this:

```
QT += core gui webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = application
TEMPLATE = app

SOURCES  += main.cpp

include($$PWD/libs/qthelper/qthelper.pri)
```

Add application classes:

```
include($$PWD/libs/qthelper/application/application.pri)
```

Add net classes:

```
include($$PWD/libs/qthelper/net/net.pri)
```

Only add a class, example Debugger:

```
SOURCE += $$PWD/libs/qthelper/application/debugger/debugger.cpp

HEADERS += $$PWD/libs/qthelper/application/debugger/debugger.h
```
