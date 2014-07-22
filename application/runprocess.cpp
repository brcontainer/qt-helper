/*
qt-helper 0.0.1
Copyright (c) 2014 Guilherme Nascimento (brcontainer@yahoo.com.br)

Released under the MIT license
*/

#include "runprocess.h"
#include <QFile>

runProcess::runProcess(QObject *parent) :
    QThread(parent),
    vp(false)
{
}

void runProcess::run() {
    runMain();
}

void runProcess::stop() {
    if(vp == false) {
        vp = true;
        terminate();
        wait();
    }
}

bool runProcess::test(const QString f) {
    QFile f1(f);
    if(f1.exists()) {
        if(!f1.remove()) {
            return false;
        }
    }
    f1.close();

    QFile f2(f);
    if(f2.exists()) {
        return false;
    }
    if(f2.open(QIODevice::WriteOnly | QIODevice::Text) == false) {
        return false;
    }
    f2.close();

    return true;
}

void runProcess::setup(const QString q) {
    f = q;
}

void runProcess::runMain() {
    QFile f1(f);
    if(f1.open(QIODevice::WriteOnly | QIODevice::Text) == false) {
        emit alreadyRunning();
        stop();
        return;
    }

    while(parent() != 0) {
        if(vp) {
            break;
        } else {
            QThread::msleep(10);
        }
    }
    f1.close();
    stop();
}
