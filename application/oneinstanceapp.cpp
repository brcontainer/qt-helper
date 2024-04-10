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
#include <QLockFile>
#include <QStandardPaths>
#include <QString>

OneInstanceApp::OneInstanceApp(int &argc, char **argv) : QApplication(argc, argv)
{
}

int OneInstanceApp::exec(const QString &file)
{
    const QString appDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    QDir(appDir).mkdir(".");

    QLockFile lock(appDir + "/" + file);

    if (!lock.tryLock(200)) {
        return -42;
    }

    return QApplication::exec();
}
