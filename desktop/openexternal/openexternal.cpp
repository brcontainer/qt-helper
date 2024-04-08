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

bool OpenExternal::showInFolder(QString file)
{
    file = file.replace("//", "/").replace("\\\\", "\\");

    bool showed = false;

    if (!QFile(file).exists()) {
        return false;
    }

    const QString uri = QDir::toNativeSeparators(file);

#if defined(Q_OS_WIN)
    showed = QProcess::startDetached("explorer", QStringList() << "/select," << uri);
#elif defined(Q_OS_OSX)
    showed = QProcess::startDetached("open", QStringList() << "-R" << uri);
#endif

    if (showed) {
        return showed;
    }

    const QString fi = "file:///" +
                        QFileInfo(uri)
                            .absoluteDir()
                                .canonicalPath()
                                    .replace("#", "%23");

    return url(fi);
}

bool OpenExternal::local(QString file)
{
    return url("file:///" + file.replace("#", "%23")) || showInFolder(file);
}

bool OpenExternal::url(QString uri)
{
    return QDesktopServices::openUrl(QUrl(uri));
}
