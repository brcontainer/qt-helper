/*
qt-helper 0.0.1
Copyright (c) 2014 Guilherme Nascimento (brcontainer@yahoo.com.br)

Released under the MIT license
*/

#include "debugger.h"
#include <QDebug>

bool enable = true;

debugger::debugger(const bool active) {
    enable = active;
}

void debugger::show(QChar t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(bool t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(char t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(signed short t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(unsigned short t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(signed int t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(unsigned int t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}
void debugger::show(signed long t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(unsigned long t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(qint64 t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(quint64 t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(float t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(double t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(const char* t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(const QString & t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}
void debugger::show(const QStringRef & t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(QLatin1String t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}
void debugger::show(const QByteArray & t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(const void * t) {
    if(enable) {
        qDebug() << t;
    } else {
        Q_UNUSED(t);
    }
}

void debugger::show(QTextStreamFunction f) {
    if(enable) {
        qDebug() << f;
    } else {
        Q_UNUSED(f);
    }
}

void debugger::show(QTextStreamManipulator m) {
    if(enable) {
        qDebug() << m;
    } else {
        Q_UNUSED(m);
    }
}

void debugger::show(QObject *o) {
    if(enable) {
        qDebug() << o;
    } else {
        Q_UNUSED(o);
    }
}

void debugger::show(QObject o) {
    if(enable) {
        qDebug() << "[" << o.objectName() << "]";
    } else {
        Q_UNUSED(o);
    }
}
