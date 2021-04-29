/*
 * qt-helper
 *
 * Copyright (c) 2021 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "network.h"

#include <QNetworkInterface>
#include <QNetworkCookieJar>
#include <QNetworkDiskCache>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDir>

Network::Network(QObject *parent) : QNetworkAccessManager(parent)
{
    setCookieJar(new QNetworkCookieJar(this));
}

QNetworkReply * Network::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
    if (request.hasRawHeader("X-QtHelper-Rewrited")) {
        return QNetworkAccessManager::createRequest(op, request, outgoingData);
    }

    if (networkAccessible() != NetworkAccessibility::Accessible) {
        tryReconnect();
    }

    const QString scheme = request.url().scheme().toLower().trimmed();

    if (scheme != "http" && scheme != "https") {
        QNetworkReply *reply = 0;

        emit proxyByScheme(scheme, reply);

        if (reply != 0) {
            return reply;
        }
    }

    const QList<QByteArray> headers = request.rawHeaderList();

    bool hasContentType = false;
    int j = headers.length();

    QNetworkRequest req(request.url());

    req.setRawHeader("X-QtHelper-Rewrited", "true");

    for (int i = 0; i < j; i++) {
        req.setRawHeader(headers[i], request.rawHeader(headers[i]));

        if (QString(headers[i]).toLower() == "content-type") {
            hasContentType = true;
        }
    }

    if ((op == PostOperation || op == PutOperation) && hasContentType == false) {
        req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    }

    if ("file" == scheme) {
        const QString path = request.url().url()
                .replace(QRegExp("^(file[:]///|file[:]//)", Qt::CaseInsensitive), "");

        if (QDir(path).exists()) {
            //network.cpp: unsupported file folder
        }
    } else if ("ftp" == scheme) {
        //"network.cpp: Unsupported FTP"
    }

    QNetworkReply *reply;

    if (op == PostOperation || op == PutOperation) {
        if (hasContentType == false) {
            req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        }

        if (op == PostOperation) {
            reply = post(req, outgoingData->readAll());
        } else {
            reply = put(req, outgoingData->readAll());
        }
    } else if (op == DeleteOperation) {
        reply = deleteResource(req);
    } else if (op == HeadOperation) {
        reply = head(req);
    } else {
        reply = get(req);
    }

    return reply;
}

void Network::tryReconnect()
{
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();

    for (int i = 0; i < ifaces.count(); i++) {
        QNetworkInterface iface = ifaces.at(i);

        if (iface.flags().testFlag(QNetworkInterface::IsUp) &&
                !iface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            setNetworkAccessible(NetworkAccessibility::Accessible);
            break;
        }
    }
}
