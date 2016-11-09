/*
 * qt-helper
 *
 * Copyright (c) 2016 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "network.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDir>
#include <QDebug>

Network::Network(QObject *parent) : QNetworkAccessManager(parent)
{
    originalNetwork = new QNetworkAccessManager(this);
}

QNetworkReply * Network::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
    const QString scheme = request.url().scheme().toLower().trimmed();

    if("file" == scheme) {
        if(
            QDir(
                request.url().url().replace(
                    QRegExp("^(file[:]///|file[:]//)", Qt::CaseInsensitive), ""
                )
            ).exists()
        ) {
            //network.cpp: unsupported file folder
        }
    } else if ("ftp" == scheme) {
        //"network.cpp: Unsupported FTP"
    }

    const QList<QByteArray> headers = request.rawHeaderList();

    bool hasContentType = false;
    int j = headers.length();
    int i = 0;

    QNetworkRequest req(request.url());

    for (; i < j; i++) {
        req.setRawHeader(headers[i], request.rawHeader(headers[i]));

        if (QString(headers[i]).toLower() == "content-type") {
            hasContentType = true;
        }
    }

    QNetworkReply *reply;

    if (op == PostOperation || op == PutOperation) {
        if(hasContentType == false) {
            //If don't have "Content-Type" then force "application/x-www-form-urlencoded"
            req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        }

        const QByteArray data = outgoingData->readAll();

        if (op == PostOperation) {
            reply = originalNetwork->post(req, data);
        } else {
            reply = originalNetwork->put(req, data);
        }
    } else if(op == DeleteOperation) {
        reply = deleteResource(req);
    } else if(op == HeadOperation) {
        reply = originalNetwork->head(req);
    } else {
        reply = originalNetwork->get(req);
    }

    return reply;
}
