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
#include <QString>
#include <QSharedMemory>

class OneInstanceApp : public QApplication
{
    Q_OBJECT

public:
    OneInstanceApp(const QString &key, int &argc, char **argv);
    virtual ~OneInstanceApp();
    bool locked() const;
    int exec() const;

private:
    QSharedMemory *mem;
    bool lock;
};

#endif // ONEINSTANCEAPP_H
