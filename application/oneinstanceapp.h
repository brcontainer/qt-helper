#ifndef ONEINSTANCEAPP_H
#define ONEINSTANCEAPP_H

/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QApplication>

class QString;

class OneInstanceApp : public QApplication
{
    Q_OBJECT

public:
    OneInstanceApp(int &argc, char **argv);
    static int exec(const QString &filepath);
};

#endif // ONEINSTANCEAPP_H
