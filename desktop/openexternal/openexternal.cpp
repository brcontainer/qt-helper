/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "openexternal.h"

#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QUrl>
#include <QDebug>

bool OpenExternal::showInFolder(const QString &path)
{
    if (!QFile(path).exists()) {
        return false;
    }

    const QString uri = QDir::toNativeSeparators(path);

#if defined(Q_OS_WIN)
    return QProcess::startDetached("explorer", QStringList() << "/select," << uri);
#else
    return QProcess::startDetached("open", QStringList() << "-R" << uri);
#endif
}

bool OpenExternal::open(const QString &path)
{
    return QDesktopServices::openUrl(QUrl(QString(path).replace("#", "%23"))) || showInFolder(path);
}
