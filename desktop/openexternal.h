#ifndef OPENEXTERNAL_H
#define OPENEXTERNAL_H

/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QString>
#include <QRegularExpression>

class OpenExternal
{

public:
    static bool showInFolder(const QString &path);
    static bool open(const QString &path);

private:
    static QString adjust(const QString &path);
};

#endif // OPENEXTERNAL_H
