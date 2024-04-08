/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "debugger.h"
#include <QDebug>

bool Debugger::enable = true;

void Debugger::setEnable(const bool active)
{
    Debugger::enable = active;
}

void Debugger::show(QChar t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(bool t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(char t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(signed short t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(unsigned short t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(signed int t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(unsigned int t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}
void Debugger::show(signed long t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(unsigned long t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(qint64 t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(quint64 t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(float t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(double t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(const char* t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(const QString & t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}
void Debugger::show(const QStringRef & t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(QLatin1String t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}
void Debugger::show(const QByteArray & t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(const void * t)
{
    if (Debugger::enable) {
        qDebug() << t;
    }
}

void Debugger::show(QTextStreamFunction f)
{
    if (Debugger::enable) {
        qDebug() << f;
    } else {
        Q_UNUSED(f);
    }
}

void Debugger::show(QTextStreamManipulator m)
{
    if (Debugger::enable) {
        qDebug() << m;
    } else {
        Q_UNUSED(m);
    }
}

void Debugger::show(QObject *o)
{
    if (Debugger::enable) {
        qDebug() << o;
    } else {
        Q_UNUSED(o);
    }
}

void Debugger::show(QObject o)
{
    if (Debugger::enable) {
        qDebug() << "[" << o.objectName() << "]";
    } else {
        Q_UNUSED(o);
    }
}
