/*
qt-helper 0.0.1
Copyright (c) 2014 Guilherme Nascimento (brcontainer@yahoo.com.br)

Released under the MIT license
*/

#include "openexternal.h"
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QFileInfo>
#include <QDesktopServices>

openExternal::openExternal(QObject *parent) :
    QThread(parent)
{
}

void openExternal::local(const QString a, QObject *parent) {
    openExternal *b = new openExternal(parent);
    b->setUrl(a, true);//true = local files
    b->start();
}

void openExternal::url(const QString a, QObject *parent) {
    openExternal *b = new openExternal(parent);
    b->setUrl(a, false);//false = non local file (eg. webpages)
    b->start();
}

void openExternal::setUrl(const QString a, const bool b) {
    uri = a;
    isLocal = b;
}

void openExternal::init() {
    if(isLocal == true) {
        //Open with DesktopService
        if(!QDesktopServices::openUrl(QUrl(uri.replace("#", "%23")))) {
            //If failed in open file, find in "explorer" (windows)
            bool o = false;
            #if defined(Q_OS_WIN)
				//Open explorer in Windows
                if(QFile(uri).exists()) {
                    QStringList params;
                    params << QLatin1String("/select,");
                    params << QDir::toNativeSeparators(uri);
                    if(QProcess::startDetached("explorer", params)) {
                        o = true;
                    }
                }
            #endif

            if(o==false) {
                //Open folder with DesktopService (If file non exists or "block")
                QFileInfo fi(uri);
                QDesktopServices::openUrl(QUrl("file:///" + fi.absoluteDir().canonicalPath().replace("#", "%23")));//Replace # by %23
            }
        }
    } else {
        //Find an App for try open an other urls (non file)
        QDesktopServices::openUrl(QUrl(uri));
    }

    //terminate process
    terminate();
    wait();
}

void openExternal::run( void ) {
    init();
}
