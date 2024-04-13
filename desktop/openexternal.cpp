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

#if QT_VERSION >= 0x050000
#include <QRegularExpression>
#else
#include <QRegExp>
#endif

bool OpenExternal::showInFolder(const QString &path)
{
    const QString uri = QDir::toNativeSeparators(adjust(path));

    if (!QFile(uri).exists()) {
        return false;
    }

#if defined(Q_OS_WIN)
    return QProcess::startDetached("explorer", QStringList() << "/select," << uri);
#else
    return QProcess::startDetached("open", QStringList() << "-R" << uri);
#endif
}

bool OpenExternal::open(const QString &path)
{
    return QDesktopServices::openUrl(QUrl("file:///" + adjust(path).replace("#", "%23"))) || showInFolder(path);
}

QString OpenExternal::adjust(const QString &path)
{
#if QT_VERSION >= 0x050000
    const QRegularExpression regex("^file:[\\/]+", QRegularExpression::CaseInsensitiveOption);
#else
    const QRegExp regex("^file:[\\/]+", Qt::CaseInsensitive);
#endif

    return QUrl(QString(path).replace(regex, "")).fromPercentEncoding(path.toUtf8()).replace(regex, "");
}
