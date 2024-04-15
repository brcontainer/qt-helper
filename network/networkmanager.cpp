/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "networkmanager.h"

#include <QDir>
#include <QNetworkInterface>
#include <QNetworkCookieJar>
#include <QNetworkDiskCache>
#include <QNetworkReply>
#include <QBuffer>

#if QT_VERSION >= 0x050000
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif

NetworkManager::NetworkManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
    defaultSchemes << "file" << "ftp" << "http" << "https";
    httpSchemes << "http" << "https";

#if QT_VERSION >= 0x050000
    const QString appDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
    const QString appDir = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif

    diskCache = new QNetworkDiskCache(this);
    diskCache->setCacheDirectory(appDir + "/cache");

    setCache(diskCache);
    setCookieJar(new QNetworkCookieJar(this));
}

void NetworkManager::clearData()
{
    diskCache->clear();
}

QNetworkReply *NetworkManager::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
    if (request.hasRawHeader("X-QtHelper-Rewrited")) {
        return QNetworkAccessManager::createRequest(op, request, outgoingData);
    }

    const QUrl url = request.url();
    const QString scheme = url.scheme().toLower();

    /*
    if (networkAccessible() != NetworkManageribility::Accessible) {
        tryReconnect();
    }
    */

    if (!httpSchemes.contains(scheme)) {
        if ("file" == scheme && QDir(url.toString()).exists()) {
            // Future implementation: directory navigation
        } else if ("ftp" == scheme) {
            // Future implementation: display FTP contents/navigation
        } else if (!defaultSchemes.contains(scheme)) {
            // Customize response for unknown schemes
            QNetworkRequest req(QUrl("about:blank"));
            req.setRawHeader("X-QtHelper-Rewrited", "true");

            QNetworkReply *reply = 0;

            emit unknownScheme(scheme, req, reply);

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
            return post(req, outgoingData->readAll());
        } else {
            return put(req, outgoingData->readAll());
        }
    } else if (op == DeleteOperation) {
        return deleteResource(req);
    } else if (op == HeadOperation) {
        return head(req);
    }

    return get(req);
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
