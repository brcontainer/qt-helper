/*
qt-helper 0.0.1
Copyright (c) 2014 Guilherme Nascimento (brcontainer@yahoo.com.br)

Released under the MIT license
*/

#include "network.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDir>

netWork::netWork(QObject *parent) :
    QNetworkAccessManager(parent)
{
    n = new QNetworkAccessManager(parent);
}

void netWork::setConfiguration(const QNetworkConfiguration &config) {
    n->setConfiguration(config);
}

void netWork::setNetworkAccessible(NetworkAccessibility accessible) {
    n->setNetworkAccessible(accessible);
}

void netWork::setProxy(const QNetworkProxy &proxy) {
    n->setProxy(proxy);
}

void netWork::setProxyFactory(QNetworkProxyFactory *factory) {
    n->setProxyFactory(factory);
}

void netWork::setCache(QAbstractNetworkCache *cache) {
    n->setCache(cache);
}

void netWork::setCookieJar(QNetworkCookieJar *cookieJar) {
    n->setCookieJar(cookieJar);
}

QNetworkReply * netWork::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData) {
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
    } else if("ftp" == scheme) {
        //"network.cpp: Unsupported FTP"
    }

    const QList<QByteArray>a = request.rawHeaderList();

    int j = a.length();
    int i = 0;

    QNetworkRequest req(request.url());
    for(; i < j; ++i) {
        req.setRawHeader(a[i], request.rawHeader(a[i]));
    }

    QNetworkReply *p;

    if(op == PostOperation || op == PutOperation) {
        const QByteArray data = outgoingData->readAll();

        if(op == PostOperation) {
            p = n->post(req, data);
        } else {
            p = n->put(req, data);
        }
    } else if(op == DeleteOperation) {
        p = n->deleteResource(req);
    } else if(op == HeadOperation) {
        p = n->head(req);
    } else {
        p = n->get(req);
    }

    return p;
}
