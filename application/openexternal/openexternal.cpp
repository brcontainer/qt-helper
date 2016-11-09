/*
 * qt-helper
 *
 * Copyright (c) 2016 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "openexternal.h"

#include <QUrl>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QFileInfo>
#include <QDesktopServices>

bool OpenExternal::showInFolder(QString file)
{
    QStringList params;
    const QString uri = QDir::toNativeSeparators(file);
    bool showed = false;

    if (QFile(file).exists()) {
        #if defined(Q_OS_WIN)
            params << QLatin1String("/select,");
            params << uri;

            showed = QProcess::startDetached("explorer", params);
        #elif defined(Q_OS_OSX)
            params << QLatin1String("-R");
            params << uri;

            showed = QProcess::startDetached("open", params);
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

    return false;
}

bool OpenExternal::local(QString file)
{
    const QString uri = "file:///" + file.replace("#", "%23");

    // Open with DesktopService
    if (!QDesktopServices::openUrl(QUrl(uri))) {
        return showInFolder(file);
    }

    return false;
}

bool OpenExternal::url(QString uri)
{
    return QDesktopServices::openUrl(QUrl(uri));
}
