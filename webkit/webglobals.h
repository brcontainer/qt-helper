#ifndef WEBGLOBALS_H
#define WEBGLOBALS_H

/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QObject>
#include <QWebSettings>

class WebGlobals : public QObject
{
    Q_OBJECT

public:
    enum WebData {
        All,
        AppCache,
        LocalStorage,
        OfflineStorage,
        Icons,
        Temporary
    };
    WebGlobals();
    QWebSettings *configs();
    QIcon getIcon(const QString &url) const;
    void developer(const bool enable);
    void setStyle(const QString &path);
    void setFont(const int size, const QString &font);
    bool erase(const WebData &type) const;
    QString getPath(const WebData &type) const;

private:
    QWebSettings *settings;
    QString configpath;
    bool createFolder(const QString &folder) const;
    bool removeRecursively(const QString &folder) const;
};

#endif // WEBGLOBALS_H
