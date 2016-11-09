#ifndef SINGLEINSTANCE_H
#define SINGLEINSTANCE_H

/*
 * qt-helper
 *
 * Copyright (c) 2016 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QThread>
#include <QString>

class QLockFile;

class SingleInstance : public QThread
{
    Q_OBJECT

private:
    QString path;
    QLockFile *sess;

public:
    explicit SingleInstance(QObject *parent = 0);
    ~SingleInstance();
    void session(const QString filename);

protected:
    void run();

signals:
    void lockError();
    void done();
};

#endif // SINGLEINSTANCE_H
