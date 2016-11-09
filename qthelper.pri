INCLUDEPATH += $$PWD

HEADERS  += \
    $$PWD/application/debugger/debugger.h \
    $$PWD/application/keysequence/keysequence.h \
    $$PWD/application/openexternal/openexternal.h \
    $$PWD/application/singleinstance/singleinstance.h

SOURCES += \
    $$PWD/application/debugger/debugger.cpp \
    $$PWD/application/keysequence/keysequence.cpp \
    $$PWD/application/openexternal/openexternal.cpp \
    $$PWD/application/singleinstance/singleinstance.cpp

HEADERS  += \
    $$PWD/mouse/trackmouse/trackmouse.h

SOURCES += \
    $$PWD/mouse/trackmouse/trackmouse.cpp

HEADERS  += \
    $$PWD/style/proxystyle/proxystyle.h

SOURCES += \
    $$PWD/style/proxystyle/proxystyle.cpp

HEADERS  += \
    $$PWD/net/network/network.h

SOURCES += \
    $$PWD/net/network/network.cpp

HEADERS  += \
    $$PWD/webkit/webglobals/webglobals.h

SOURCES += \
    $$PWD/webkit/webglobals/webglobals.cpp
