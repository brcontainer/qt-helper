#ifndef NETWORK_H
#define NETWORK_H

/*
 * qt-helper
 *
 * Copyright (c) 2016 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QNetworkAccessManager>

class Network : public QNetworkAccessManager
{
    Q_OBJECT

private:
    QNetworkAccessManager *originalNetwork;

protected:
    virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData = 0);

public:
    explicit Network(QObject *parent = 0);
};

#endif // NETWORK_H
