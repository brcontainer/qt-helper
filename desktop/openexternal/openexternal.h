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
    static bool showInFolder(QString file);
    static bool local(QString file);
    static bool url(QString uri);
};

#endif // OPENEXTERNAL_H
