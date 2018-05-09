/*
 * qt-helper
 *
 * Copyright (c) 2018 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "singleinstance.h"

#include <QLockFile>

SingleInstance::SingleInstance(QObject *parent) : QThread(parent)
{
    sess = 0;
}

SingleInstance::~SingleInstance()
{
    if (sess != 0) {
        sess->unlock();
    }
}

void SingleInstance::session(const QString filename)
{
    path = filename;
}

void SingleInstance::run()
{
    sess = new QLockFile(path);

    if(!sess->tryLock(200)) {
        emit lockError();
    } else {
        emit done();
    }
}
