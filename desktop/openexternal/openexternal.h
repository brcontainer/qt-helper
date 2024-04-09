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

class OpenExternal
{

public:
    static bool showInFolder(const QString &path);
    static bool open(const QString &path);
};

#endif // OPENEXTERNAL_H
