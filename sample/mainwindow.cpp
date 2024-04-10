#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "action.h"
#include "openexternal.h"
#include "trackmouse.h"
#include "networkmanager.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Bind shortcut to widget
    Action::widget(this, "Ctrl+w", this, SLOT(close()));
    Action::widget(this, "F1", this, SLOT(aboutQt()));
    Action::widget(this, "F3", this, SLOT(showNormal()));
    Action::widget(this, "F4", this, SLOT(showMaximized()));
    Action::widget(this, "F5", this, SLOT(showFullScreen()));

    QObject::connect(ui->btn1, SIGNAL(clicked()), this, SLOT(loadDuckduckgo()));
    QObject::connect(ui->btn2, SIGNAL(clicked()), this, SLOT(loadHTML()));
    QObject::connect(ui->btn3, SIGNAL(clicked()), this, SLOT(openFile()));
    QObject::connect(ui->btn4, SIGNAL(clicked()), this, SLOT(showFileInFolder()));
    QObject::connect(ui->btn5, SIGNAL(clicked()), this, SLOT(tryOpenNotExists()));

    // Network manager for fix issue some servers
    NetworkManager *manager = new NetworkManager(this);

    QObject::connect(manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
                     this, SLOT(handleSslErrors(QNetworkReply*,QList<QSslError>)));

    ui->webView->page()->setNetworkAccessManager(manager);

    loadHTML();

    // Track mouse with delay
    TrackMouse *track = new TrackMouse(this);
    QObject::connect(track, SIGNAL(position(QPoint)), this, SLOT(capture(QPoint)));
    track->setDelay(1000);
    track->setWidget(this, true);
    track->enable(true);
    track->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::aboutQt()
{
    qApp->aboutQt();
}

void MainWindow::loadDuckduckgo()
{
    ui->webView->load(QUrl("https://duckduckgo.com/"));
}

void MainWindow::loadHTML()
{
    QStringList htmlContents;
    htmlContents << "<select style='width: 140px;'>";
    htmlContents << "<option>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua</option>";
    htmlContents << "<option>foo</option>";
    htmlContents << "<option>bar</option>";
    htmlContents << "<option>baz</option>";
    htmlContents << "</select>";

    ui->webView->setHtml(htmlContents.join("\n"));
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

void MainWindow::handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
    qDebug() << errors;
    reply->ignoreSslErrors();
}

void MainWindow::capture(const QPoint &pos)
{
    qDebug() << pos;
}
