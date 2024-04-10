#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QNetworkAccessManager>
#include <QStringList>

class QNetworkDiskCache;

class NetworkManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = 0);

protected:
    virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData = 0);
    void tryReconnect();

signals:
    void proxyByScheme(const QString scheme, QNetworkReply *reply);

private:
    QStringList defaultSchemes; // { "file", "ftp", "http", "https" }
    QStringList httpSchemes; // { "http", "https" }
};

#endif // NETWORKMANAGER_H
