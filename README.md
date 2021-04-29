# Qt-helper

Simple Qt library to improve and help in their projects

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

For use only "application" classes put this in your `.pro` file:

```
include($$PWD/libs/qthelper/application/application.pri)
```

- [x] debugger helpful for use `qDebug`
<<<<<<< Updated upstream
- [x] keysequence helpful key sequences for all objects
- [x] openexternal helpful for open protocols from system
- [x] singleinstance prevent open a app multiples on Desktop
=======
- [x] singleinstance prevent open a app multiples on Desktop

## Desktop

- [x] keysequence helpful key sequences for all objects
- [x] openexternal helpful for open protocols from system
- [x] `TrackMouse` used for track mouse in `QMainWindow` or other `QWidget`
>>>>>>> Stashed changes

## Style

- [x] Improved sizes, prevent trim text in select combo

## NET

For use only "net" classes put this in your `.pro` file:

```
include($$PWD/libs/qthelper/net/net.pri)
```

<<<<<<< Updated upstream
- [x] network fix bugs in download, ajax and network disabled

## Style

- [x] proxystyle corrige "pop-up" em comboboxes no WebKit
=======
- [x] network fix bugs in download, xmlhttprequest and network disabled
>>>>>>> Stashed changes

## Webkit

- [x] webglobals used for pre-setup configurations

Only add a class, example Debugger:

```
HEADERS += $$PWD/libs/qthelper/application/debugger/debugger.h

SOURCE += $$PWD/libs/qthelper/application/debugger/debugger.cpp
```
