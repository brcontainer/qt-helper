/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "oneinstanceapp.h"

#include <QDateTime>
#include <QDir>

OneInstanceApp::OneInstanceApp(const QString &key, int &argc, char **argv) :
    QApplication(argc, argv),
    lock(false)
{
    mem = new QSharedMemory(key, this);

    if (mem->attach(QSharedMemory::ReadOnly)) {
        mem->detach();
    } else if (mem->create(1)) {
        lock = true;
    }
}

OneInstanceApp::~OneInstanceApp()
{
    if (mem->attach(QSharedMemory::ReadOnly)) {
        mem->detach();
    }
}

bool OneInstanceApp::locked() const
{
    return lock;
}

int OneInstanceApp::exec() const
{
    if (!lock) {
        return -42;
    }

    return QApplication::exec();
}
