#ifndef DEBUGGER_H
#define DEBUGGER_H

/*
 * qt-helper
 *
 * Copyright (c) 2016 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QString>
#include <QObject>
#include <QTextStreamFunction>
#include <QTextStreamManipulator>

class Debugger
{

private:
    static bool enable;

public:
    Debugger(const bool active = true);
    static void show(QChar t);
    static void show(bool t);
    static void show(char t);
    static void show(signed short t);
    static void show(unsigned short t);
    static void show(signed int t);
    static void show(unsigned int t);
    static void show(signed long t);
    static void show(unsigned long t);
    static void show(qint64 t);
    static void show(quint64 t);
    static void show(float t);
    static void show(double t);
    static void show(const char* t);
    static void show(const QString & t);
    static void show(const QStringRef & t);
    static void show(QLatin1String t);
    static void show(const QByteArray & t);
    static void show(const void* t);
    static void show(QTextStreamFunction f);
    static void show(QTextStreamManipulator m);
    static void show(QObject* o);
    static void show(QObject o);
};

#endif //DEBUGGER_H
