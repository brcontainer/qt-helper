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
#include <QNetworkRequest>
#include <QStringList>

class QNetworkDiskCache;

class NetworkManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = 0);
    void clearData();

private:
    QStringList defaultSchemes;
    QStringList httpSchemes;
    QNetworkDiskCache *diskCache;

protected:
    virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData = 0);
    void tryReconnect();

signals:
    void unknownScheme(const QString &scheme, QNetworkReply *reply);
};

#endif // NETWORKMANAGER_H
