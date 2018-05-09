#ifndef WEBGLOBALS_H
#define WEBGLOBALS_H

/*
 * qt-helper
 *
 * Copyright (c) 2018 Guilherme Nascimento (brcontainer@yahoo.com.br)
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
    QIcon getIcon(const QString u) const;
    void developer(const bool enable);
    void setPath(const QString a);
    void setStyle(const QString path);
    void setFont(const int size, const QString font);
    bool erase(const WebData type) const;
    QString getPath(const WebData type) const;
    static bool createFolder(const QString folder);

private:
    QWebSettings *settings;
    QString configpath;
};

#endif // WEBGLOBALS_H
