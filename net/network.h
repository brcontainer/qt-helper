#ifndef NETWORK_H
#define NETWORK_H

/*
* Some servers do not respond to "QT script", this lib fixed the problem
*/

#include <QNetworkAccessManager>

class netWork : public QNetworkAccessManager
{
    Q_OBJECT

private:
    QNetworkAccessManager *n;

protected:
    virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData = 0);

public:
    explicit netWork(QObject *parent = 0);

public:
    void setConfiguration(const QNetworkConfiguration &config);
    void setNetworkAccessible(NetworkAccessibility accessible);
    void setProxy(const QNetworkProxy &proxy);
    void setProxyFactory(QNetworkProxyFactory *factory);
    void setCache(QAbstractNetworkCache *cache);
    void setCookieJar(QNetworkCookieJar *cookieJar);

signals:

public slots:

};

#endif // NETWORK_H
