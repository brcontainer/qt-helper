/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
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
    settings->setAttribute(QWebSettings::JavaEnabled, false);

    settings->setAttribute(QWebSettings::AutoLoadImages, true);

    settings->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
    settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);

    settings->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
    settings->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, true);
    settings->setAttribute(QWebSettings::JavascriptCanAccessClipboard, false);
    settings->setAttribute(QWebSettings::ScrollAnimatorEnabled, true);

    QWebSettings::setMaximumPagesInCache(999999);
    QWebSettings::setObjectCacheCapacities(0, 999999, 999999);

    QWebSettings::setOfflineWebApplicationCacheQuota(999999);
    QWebSettings::setOfflineStorageDefaultQuota(999999);
}

void WebGlobals::developer(const bool enable)
{
    settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, enable);
}

void WebGlobals::setPath(const QString &path)
{
    configpath = path;

    createFolder(configpath + "appcache");
    createFolder(configpath + "offlinestorage");
    createFolder(configpath + "storage");
    createFolder(configpath + "icons");
    createFolder(configpath + "tmp");

    QWebSettings::setOfflineWebApplicationCachePath(configpath + "appcache");
    QWebSettings::setOfflineStoragePath(configpath + "offlinestorage");
    QWebSettings::setIconDatabasePath(configpath + "icons");

    settings->setLocalStoragePath(configpath + "localstorage");
}

bool WebGlobals::createFolder(const QString &folder)
{
    return QDir(folder).mkpath(".");
}

QIcon WebGlobals::getIcon(const QString &url) const
{
    return settings->iconForUrl(QUrl(url));
}

void WebGlobals::setStyle(const QString &path)
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

        case OfflineStorage:
            return configpath + "offlinestorage";

        case LocalStorage:
            return configpath + "localstorage";

        case Icons:
            return configpath + "icons";

        case Temporary:
            return configpath + "tmp";

        default:
            return configpath;
    }
}

bool WebGlobals::erase(const WebData type) const
{
    switch (type)
    {
        case AppCache:
            return QDir(configpath + "appcache").removeRecursively() &&
                   createFolder(configpath + "appcache");

        case OfflineStorage:
            return QDir(configpath + "offlinestorage").removeRecursively() &&
                   createFolder(configpath + "offlinestorage");

        case LocalStorage:
            return QDir(configpath + "localstorage").removeRecursively() &&
                   createFolder(configpath + "localstorage");

        case Icons:
            settings->clearIconDatabase();

            return QDir(configpath + "icons").removeRecursively() &&
                   createFolder(configpath + "icons");

        case Temporary:
            return QDir(configpath + "tmp").removeRecursively() &&
                   createFolder(configpath + "tmp");

        default:
            return (
                erase(AppCache) &&
                erase(OfflineStorage) &&
                erase(LocalStorage) &&
                erase(Icons) &&
                erase(Temporary)
            );
    }
}

QWebSettings *WebGlobals::configs()
{
    return settings;
}

