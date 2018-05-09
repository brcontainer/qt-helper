# qt-helper

Simple QT library to improve and help in their projects

## Usage:

For use all classes add in your project something like this:

```
QT += core gui webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = application
TEMPLATE = app

SOURCES  += main.cpp

include($$PWD/libs/qthelper/qthelper.pri)
```

## Application

```
include($$PWD/libs/qthelper/application/application.pri)
```

[x] debugger helpful for use `qDebug`
[x] keysequence helpful key sequences for all objects
[x] openexternal helpful for open protocols from system
[x] singleinstance prevent open a app multiples on Desktop

## Mouse

[x] `TrackMouse` used for track mouse in `QMainWindow` or other `QWidget`

## NET

```
include($$PWD/libs/qthelper/net/net.pri)
```

[x] network fix bugs in download, ajax and network disabled

## Style

[x]

## Webkit

[x] webglobals used for pre-setup configurations

Only add a class, example Debugger:

```
SOURCE += $$PWD/libs/qthelper/application/debugger/debugger.cpp

HEADERS += $$PWD/libs/qthelper/application/debugger/debugger.h
```
