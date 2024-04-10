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

NetworkManager::NetworkManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
    defaultSchemes << "file" << "ftp" << "http" << "https";
    httpSchemes << "http" << "https";

    setCookieJar(new QNetworkCookieJar(this));
}

QNetworkReply * NetworkManager::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
    const QUrl url = request.url();
    const QString scheme = url.scheme().toLower();

    /*
    if (networkAccessible() != NetworkManageribility::Accessible) {
       tryReconnect();
    }
    */

    QNetworkReply *reply = 0;

    if (!httpSchemes.contains(scheme) || request.hasRawHeader("X-QtHelper-Rewrited")) {
        if ("file" == scheme && QDir(url.url()).exists()) {
            // Future implementation: directory navigation
        } else if ("ftp" == scheme) {
            // Future implementation: display FTP contents/navigation
        } else if (!defaultSchemes.contains(scheme)) {
            // Customize response for unknown schemes

            emit proxyByScheme(scheme, reply);

            if (reply != 0) {
                return reply;
            }
        }

        return QNetworkAccessManager::createRequest(op, request, outgoingData);
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
