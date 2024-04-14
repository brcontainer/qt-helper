#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "openexternal.h"
#include "shortcut.h"
#include "trackmouse.h"

#include <QDebug>
#include <QSslError>

#include <QWebPage>
#include <QWebView>
#include <QNetworkDiskCache>

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Bind shortcut to widget
    Shortcut::keys(this, "Ctrl+w", this, SLOT(close()));
    Shortcut::keys(this, "F1", this, SLOT(aboutQt()));
    Shortcut::keys(this, "F3", this, SLOT(showNormal()));
    Shortcut::keys(this, "F4", this, SLOT(showMaximized()));
    Shortcut::keys(this, "F5", this, SLOT(showFullScreen()));
    Shortcut::keys(this, QKeySequence::WhatsThis, this, SLOT(whatThis())); // Shit+F1

    QObject::connect(ui->btn1, SIGNAL(clicked()), this, SLOT(loadDuckduckgo()));
    QObject::connect(ui->btn2, SIGNAL(clicked()), this, SLOT(loadHTML()));
    QObject::connect(ui->btn3, SIGNAL(clicked()), this, SLOT(clearBrowserData()));
    QObject::connect(ui->btn4, SIGNAL(clicked()), this, SLOT(openFile()));
    QObject::connect(ui->btn5, SIGNAL(clicked()), this, SLOT(showFileInFolder()));
    QObject::connect(ui->btn6, SIGNAL(clicked()), this, SLOT(tryOpenNotExists()));

    webconfig = new WebGlobals();
    webconfig->developer(true);

    qDebug() << "WebGlobals::All:" << webconfig->getPath(WebGlobals::All);
    qDebug() << "WebGlobals::AppCache:" << webconfig->getPath(WebGlobals::AppCache);
    qDebug() << "WebGlobals::LocalStorage:" << webconfig->getPath(WebGlobals::LocalStorage);
    qDebug() << "WebGlobals::OfflineStorage:" << webconfig->getPath(WebGlobals::OfflineStorage);
    qDebug() << "WebGlobals::Icons:" << webconfig->getPath(WebGlobals::Icons);
    qDebug() << "WebGlobals::Temporary:" << webconfig->getPath(WebGlobals::Temporary);

    webView = new QWebView(this);
    ui->webViewFrame->layout()->addWidget(webView);

    QWebPage *page = webView->page();
    page->setForwardUnsupportedContent(true);

    // Network manager for fix issue some servers
    manager = new NetworkManager(this);

    QObject::connect(manager, SIGNAL(unknownScheme(QString,QNetworkReply*)),
                     this, SLOT(unknownScheme(QString,QNetworkReply*)));

    QObject::connect(manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
                     this, SLOT(handleSslErrors(QNetworkReply*,QList<QSslError>)));

    page->setNetworkAccessManager(manager);

    QObject::connect(webView, SIGNAL(loadStarted()), this, SLOT(loadProgress()));
    QObject::connect(webView, SIGNAL(loadProgress(int)), this, SLOT(loadProgress(int)));
    QObject::connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(loadProgress()));

    QObject::connect(webView, SIGNAL(titleChanged(QString)), this, SLOT(titleChanged(QString)));
    QObject::connect(webView, SIGNAL(statusBarMessage(QString)), this, SLOT(statusBarMessage(QString)));
    QObject::connect(webView, SIGNAL(iconChanged()), this, SLOT(iconChanged()));

    QObject::connect(page, SIGNAL(unsupportedContent(QNetworkReply*)),
                     this, SLOT(unsupportedContent(QNetworkReply*)));

    QObject::connect(page, SIGNAL(downloadRequested(QNetworkRequest)),
                     this, SLOT(download(QNetworkRequest)));

    loadHTML();

    // Track mouse with delay
    TrackMouse *track = new TrackMouse(this);
    QObject::connect(track, SIGNAL(position(QPoint)), this, SLOT(capture(QPoint)));
    track->setDelay(500);
    track->setWidget(this, true);
    track->enable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::aboutQt()
{
    qApp->aboutQt();
}

void MainWindow::whatThis()
{
    qDebug() << "What This";
}

void MainWindow::loadDuckduckgo()
{
    webView->load(QUrl("https://duckduckgo.com/"));
}

void MainWindow::loadHTML()
{
    QStringList htmlContents;
    htmlContents << "<select style='width: 140px;'>";
    htmlContents << "<optgroup label='Group 1'>";
    htmlContents << "<option>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed";
    htmlContents << "do eiusmod tempor incididunt ut labore et dolore magna aliqua</option>";
    htmlContents << "<option>foo</option>";
    htmlContents << "<option>bar</option>";
    htmlContents << "<option>baz</option>";
    htmlContents << "</optgroup>";
    htmlContents << "<optgroup label='Group 2'>";
    htmlContents << "<option>foo</option>";
    htmlContents << "<option>bar</option>";
    htmlContents << "<option>WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW</option>";
    htmlContents << "</optgroup>";
    htmlContents << "</select>";
    htmlContents << " ";
    htmlContents << "<select style='width: 140px;'>";
    htmlContents << "<option>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed</option>";
    htmlContents << "<option>foo</option>";
    htmlContents << "<option>bar</option>";
    htmlContents << "<option>baz</option>";
    htmlContents << "<option>WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW</option>";
    htmlContents << "</select>";
    htmlContents << "<hr>";
    htmlContents << "<a href='mailto:foo@bar.baz'>mailto:foo@bar.baz</a>,";
    htmlContents << "<a href='tel:+55010101010101'>+55010101010101</a>,";
    htmlContents << "<a href='telegram:@foobar'>telegram:@foobar</a>,";
    htmlContents << "<a href='skype:+55010101010101'>skype:+55010101010101</a>";

    webView->setHtml(htmlContents.join("\n"));
}

void MainWindow::clearBrowserData()
{
    manager->clearData();
    qDebug() << "Clear icons, database:" << webconfig->erase(WebGlobals::All);
}

void MainWindow::openFile()
{
    OpenExternal::open("C:/foo/bar/pic_400x400#.jpg");
}

void MainWindow::showFileInFolder()
{
    OpenExternal::showInFolder("C:/foo/bar/pic_400x400#.jpg");
}

void MainWindow::tryOpenNotExists()
{
    OpenExternal::open("C:/foo/bar/invalid.jpg");
}

void MainWindow::unknownScheme(const QString &scheme, QNetworkReply *reply)
{
    qDebug() << scheme << "=>" << reply->url().toString();
}

void MainWindow::handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
    Q_FOREACH(QSslError info, errors) {
        qDebug() << "handleSslErrors:" << info.errorString();
    }

    reply->ignoreSslErrors();
}

void MainWindow::loadProgress(const int value)
{
    ui->progressBar->setValue(value == 100 ? 0 : value);
}

void MainWindow::titleChanged(const QString &title)
{
    // qDebug() << "TITLE CHANGED: " << title;
    setWindowTitle(title);
}

void MainWindow::statusBarMessage(const QString &message)
{
    ui->webStatusText->setText(message);
}

void MainWindow::iconChanged()
{
    setWindowIcon(webView->icon());
}

void MainWindow::unsupportedContent(QNetworkReply* reply)
{
    qDebug() << "unsupported content:" << reply->url().toString();
    webView->stop();
}

void MainWindow::download(const QNetworkRequest &request)
{
    qDebug() << "Download:" << request.url().toString();
}

void MainWindow::capture(const QPoint &pos)
{
    ui->mousePositionText->setText(QString("%1x%2").arg(pos.x()).arg(pos.y()));
}
