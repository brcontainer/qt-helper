#ifndef RUNPROCESS_H
#define RUNPROCESS_H

/*
qt-helper 0.0.1
Copyright (c) 2014 Guilherme Nascimento (brcontainer@yahoo.com.br)

Released under the MIT license
*/

#include <QThread>
#include <QString>

class runProcess : public QThread
{
    Q_OBJECT

private:
    bool vp;
    QString f;

public:
    explicit runProcess(QObject *parent = 0);

public:
    void setup(const QString q);
    static bool test(const QString f);

signals:
    void alreadyRunning();

public slots:
    void stop();

protected:
    virtual void run(void);

private:
    void runMain();

};

#endif // RUNPROCESS_H
