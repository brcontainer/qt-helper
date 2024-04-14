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

#if QT_VERSION >= 0x050000
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif

WebGlobals::WebGlobals()
{
#if QT_VERSION >= 0x050000
    configpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
    configpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif

    createFolder(configpath);
    createFolder(getPath(AppCache));
    createFolder(getPath(LocalStorage));
    createFolder(getPath(Icons));
    createFolder(getPath(OfflineStorage));
    createFolder(getPath(AppCache));

    settings = QWebSettings::globalSettings();

    settings->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    settings->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    settings->setAttribute(QWebSettings::LocalStorageEnabled, true);
    settings->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    settings->setAttribute(QWebSettings::JavascriptCanCloseWindows, true);
    settings->setAttribute(QWebSettings::JavascriptEnabled, true);

    // Enable OpenGL/webGL
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

#if QT_VERSION >= 0x050000
    settings->setAttribute(QWebSettings::ScrollAnimatorEnabled, true);
#endif

    QWebSettings::setMaximumPagesInCache(999999);
    QWebSettings::setObjectCacheCapacities(0, 999999, 999999);

    QWebSettings::setOfflineWebApplicationCacheQuota(999999);
    QWebSettings::setOfflineStorageDefaultQuota(999999);
    settings->setLocalStoragePath(getPath(LocalStorage));

    QWebSettings::setIconDatabasePath(getPath(Icons));
    QWebSettings::setOfflineStoragePath(getPath(OfflineStorage));
    QWebSettings::setOfflineWebApplicationCachePath(getPath(AppCache));
}

void WebGlobals::developer(const bool enable)
{
    settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, enable);
}

bool WebGlobals::createFolder(const QString &folder) const
{
    return QDir(configpath).mkpath(folder);
}

QIcon WebGlobals::getIcon(const QString &url) const
{
    return settings->iconForUrl(QUrl(url));
}

void WebGlobals::setStyle(const QString &path)
{
    settings->setUserStyleSheetUrl(QUrl(path));
}

void WebGlobals::setFont(const int size, const QString &font)
{
    settings->setFontSize(QWebSettings::DefaultFontSize, size);
    settings->setFontFamily(QWebSettings::StandardFont, font);
}

bool WebGlobals::erase(const WebData &type) const
{
    QString path;

    if (type == AppCache) {
        path = getPath(AppCache);
        return removeRecursively(path) && createFolder(path);
    }

    if (type == OfflineStorage) {
        path = getPath(OfflineStorage);
        return removeRecursively(path) && createFolder(path);
    }

    if (type == LocalStorage) {
        path = getPath(LocalStorage);
        return removeRecursively(path) && createFolder(path);
    }

    if (type == Icons) {
        path = getPath(Icons);
        settings->clearIconDatabase();
        return true;
    }

    QWebSettings::clearMemoryCaches();

    return (
        erase(AppCache) &&
        erase(OfflineStorage) &&
        erase(LocalStorage) &&
        erase(Icons)
    );
}

QString WebGlobals::getPath(const WebData &type) const
{
    switch (type)
    {
        case AppCache:
            return QDir::toNativeSeparators(configpath + "/appcache");

        case OfflineStorage:
            return QDir::toNativeSeparators(configpath + "/offlinestorage");

        case LocalStorage:
            return QDir::toNativeSeparators(configpath + "/localstorage");

        case Icons:
            return QDir::toNativeSeparators(configpath + "/icons");

        case Temporary:
            return QDir::toNativeSeparators(configpath + "/tmp");

        default:
            return QDir::toNativeSeparators(configpath);
    }
}

bool WebGlobals::removeRecursively(const QString &folder) const
{
#if QT_VERSION >= 0x050000
    return QDir(folder).removeRecursively();
#else
    bool result = true;

    QDir dir(folder);

    if (dir.exists()) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeRecursively(info.absoluteFilePath());
            } else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }

        result = QDir().rmdir(folder);
    }

    return result;
#endif
}

QWebSettings *WebGlobals::configs()
{
    return settings;
}

