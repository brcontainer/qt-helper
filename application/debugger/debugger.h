#ifndef DEBUGGER_H
#define DEBUGGER_H

/*
 * qt-helper
 *
 * Copyright (c) 2018 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QObject>
#include <QString>
#include <QTextStreamFunction>
#include <QTextStreamManipulator>

namespace Debugger
{
    extern bool enable;

    void setEnable(const bool active);
    void show(QChar t);
    void show(bool t);
    void show(char t);
    void show(signed short t);
    void show(unsigned short t);
    void show(signed int t);
    void show(unsigned int t);
    void show(signed long t);
    void show(unsigned long t);
    void show(qint64 t);
    void show(quint64 t);
    void show(float t);
    void show(double t);
    void show(const char* t);
    void show(const QString & t);
    void show(const QStringRef & t);
    void show(QLatin1String t);
    void show(const QByteArray & t);
    void show(const void* t);
    void show(QTextStreamFunction f);
    void show(QTextStreamManipulator m);
    void show(QObject* o);
    void show(QObject o);
}

#endif //DEBUGGER_H
