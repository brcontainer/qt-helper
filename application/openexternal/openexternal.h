#ifndef OPENEXTERNAL_H
#define OPENEXTERNAL_H

/*
 * qt-helper
 *
 * Copyright (c) 2016 Guilherme Nascimento (brcontainer@yahoo.com.br)
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
