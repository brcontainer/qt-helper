/*
 * qt-helper
 *
 * Copyright (c) 2016 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "webglobals.h"
#include <QDir>
#include <QUrl>

WebGlobals::WebGlobals()
{
    settings = QWebSettings::globalSettings();
    settings->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    settings->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    settings->setAttribute(QWebSettings::LocalStorageEnabled, true);
    settings->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    settings->setAttribute(QWebSettings::JavascriptCanCloseWindows, true);
    settings->setAttribute(QWebSettings::JavascriptEnabled, true);

    //Enable OpenGL/webGL
    settings->setAttribute(QWebSettings::AcceleratedCompositingEnabled, true);
    settings->setAttribute(QWebSettings::WebGLEnabled, true);

    settings->setAttribute(QWebSettings::PluginsEnabled, true);
    settings->setAttribute(QWebSettings::JavaEnabled, false); //Desabilita java

    settings->setAttribute(QWebSettings::AutoLoadImages, true);

    settings->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
    settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);

    settings->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
    settings->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, true);
    settings->setAttribute(QWebSettings::JavascriptCanAccessClipboard, false);
    settings->setAttribute(QWebSettings::ScrollAnimatorEnabled, true);
}

void WebGlobals::developer(const bool enable)
{
    settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, enable);
}

void WebGlobals::setPath(const QString path)
{
    configpath = path;

    createFolder(configpath + "appcache");
    createFolder(configpath + "offlinestorage");
    createFolder(configpath + "storage");
    createFolder(configpath + "icons");
    createFolder(configpath + "tmp");

    settings->setOfflineWebApplicationCachePath(configpath + "appcache");
    settings->setOfflineStoragePath(configpath + "offlinestorage");
    settings->setLocalStoragePath(configpath + "localstorage");
    settings->setIconDatabasePath(configpath + "icons");
}

bool WebGlobals::createFolder(const QString folder)
{
    QDir tmp;

    if (false == tmp.exists(folder) && false == tmp.mkpath(folder)) {
        return false;
    }

    return true;
}

QIcon WebGlobals::getIcon(const QString u) const
{
    return settings->iconForUrl(QUrl(u));
}

void WebGlobals::setStyle(const QString path)
{
    settings->setUserStyleSheetUrl(QUrl(path));
}

void WebGlobals::setFont(const int size, const QString font)
{
    settings->setFontSize(QWebSettings::DefaultFontSize, size);
    settings->setFontFamily(QWebSettings::StandardFont, font);
}

QString WebGlobals::getPath(const WebData type) const
{
    switch (type)
    {
        case AppCache:
            return configpath + "appcache";
        break;
        case OfflineStorage:
            return configpath + "offlinestorage";
        break;
        case LocalStorage:
            return configpath + "localstorage";
        break;
        case Icons:
            return configpath + "icons";
        break;
        case Temporary:
            return configpath + "tmp";
        break;
        default:
            return configpath;
    }
}

bool WebGlobals::remove(const WebData type) const
{
    switch (type)
    {
        case AppCache:
            return QDir(configpath + "appcache").removeRecursively();
        break;
        case OfflineStorage:
            return QDir(configpath + "offlinestorage").removeRecursively();
        break;
        case LocalStorage:
            return QDir(configpath + "localstorage").removeRecursively();
        break;
        case Icons:
            return QDir(configpath + "icons").removeRecursively();
        break;
        case Temporary:
            return QDir(configpath + "tmp").removeRecursively();
        break;
        default:
            return (
                remove(AppCache) &&
                remove(OfflineStorage) &&
                remove(LocalStorage) &&
                remove(Icons) &&
                remove(Temporary)
            );
    }
}

QWebSettings *WebGlobals::configs()
{
    return settings;
}

