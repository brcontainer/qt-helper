This class eases enable or disable the logs (`qDebug()`) at different locations (different classes).

Usage:

main.cpp:

```cpp
#include "debugger.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//show "logs" only in DEBUG (build in debug)
#ifdef QT_DEBUG
    Debugger(true);
#else
    Debugger(false);
#endif

    Debugger::show("main.cpp");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
```

mainwindow.cpp:

```cpp
#include "debugger.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    debugger::show("mainwindow.cpp: Create MainWindow");
}

MainWindow::~MainWindow()
{
    debugger::show("mainwindow.cpp: Delete MainWindow");

    delete ui;
}
```
