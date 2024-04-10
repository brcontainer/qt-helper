#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void aboutQt();
    void loadDuckduckgo();
    void loadHTML();
    void openFile();
    void showFileInFolder();
    void tryOpenNotExists();
    void handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors);
    void capture(const QPoint &pos);
};

#endif // MAINWINDOW_H
