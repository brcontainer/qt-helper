#ifndef NETWORK_H
#define NETWORK_H

/*
 * qt-helper
 *
 * Copyright (c) 2021 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QNetworkAccessManager>

class QNetworkDiskCache;

class Network : public QNetworkAccessManager
{
    Q_OBJECT

public:
    explicit Network(QObject *parent = 0);

protected:
    virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData = 0);
    void tryReconnect();

signals:
    void proxyByScheme(const QString scheme, QNetworkReply *reply);
};

#endif // NETWORK_H
