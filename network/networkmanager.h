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
    void tryReconnect();
    virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData = 0);

signals:
    void unknownScheme(const QString &scheme, const QNetworkRequest &request, QNetworkReply *reply);
};

#endif // NETWORKMANAGER_H
