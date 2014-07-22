#ifndef OPENEXTERNAL_H
#define OPENEXTERNAL_H

/*
qt-helper 0.0.1
Copyright (c) 2014 Guilherme Nascimento (brcontainer@yahoo.com.br)

Released under the MIT license
*/

/*
* Open external applications can sometimes cause crashes/freezes (especially when we use "QDesktopServices::openUrl")
*/

#include <QThread>

class openExternal : public QThread
{
    Q_OBJECT

private:
    bool isLocal;
    QString uri;
    void setUrl(const QString a, const bool b = false);
    void init();

public:
    explicit openExternal(QObject *parent = 0);
    static void local(const QString a, QObject *parent = 0);
    static void url(const QString a, QObject *parent = 0);

protected:
    virtual void run(void);
};

#endif // OPENEXTERNAL_H
