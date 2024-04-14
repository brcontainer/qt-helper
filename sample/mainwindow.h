#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "networkmanager.h"
#include "webglobals.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QWebView;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWebView *webView;
    WebGlobals *webconfig;
    NetworkManager *manager;

public slots:
    void aboutQt();
    void whatThis();
    void loadDuckduckgo();
    void loadHTML();
    void clearBrowserData();
    void openFile();
    void showFileInFolder();
    void tryOpenNotExists();
    void unknownScheme(const QString &scheme, QNetworkReply *reply);
    void handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors);
    void loadProgress(const int value = 0);
    void titleChanged(const QString &title);
    void statusBarMessage(const QString &message);
    void iconChanged();

    void unsupportedContent(QNetworkReply* reply);
    void download(const QNetworkRequest &request);
    void capture(const QPoint &pos);
};
#endif // MAINWINDOW_H
