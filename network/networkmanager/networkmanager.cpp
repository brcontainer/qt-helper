/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "networkmanager.h"

#include <QNetworkInterface>
#include <QNetworkCookieJar>
#include <QNetworkDiskCache>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDir>

NetworkManager::NetworkManager(QObject *parent) : QNetworkAccessManager(parent)
{
    setCookieJar(new QNetworkCookieJar(this));
}

QNetworkReply * NetworkManager::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
    if (request.hasRawHeader("X-QtHelper-Rewrited")) {
        return QNetworkAccessManager::createRequest(op, request, outgoingData);
    }

    // if (networkAccessible() != NetworkManageribility::Accessible) {
    //    tryReconnect();
    // }

    const QUrl url = request.url();
    const QString scheme = url.scheme().toLower();

    if ("http" != scheme && "https" != scheme) {
        QNetworkReply *reply = 0;

        emit proxyByScheme(scheme, reply);

        if (reply != 0) {
            return reply;
        }
    }

    const QList<QByteArray> headers = request.rawHeaderList();

    bool hasContentType = false;
    int j = headers.length();

    QNetworkRequest req(url);

    req.setRawHeader("X-QtHelper-Rewrited", "true");

    for (int i = 0; i < j; i++) {
        req.setRawHeader(headers[i], request.rawHeader(headers[i]));

        if (QString(headers[i]).toLower() == "content-type") {
            hasContentType = true;
        }
    }

    if (hasContentType == false && (op == PostOperation || op == PutOperation)) {
        req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    }

    if ("file" == scheme) {
        if (QDir(url.url()).exists()) {
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

void NetworkManager::tryReconnect()
{
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    const int j = ifaces.count();

    for (int i = 0; i < j; i++) {
        // QNetworkInterface iface = ifaces.at(i);
        const QNetworkInterface::InterfaceFlags flags = ifaces.at(i).flags();

        if (flags.testFlag(QNetworkInterface::IsUp) && !flags.testFlag(QNetworkInterface::IsLoopBack))
        {
            // setNetworkManagerible(NetworkManageribility::Accessible);
            break;
        }
    }
}
