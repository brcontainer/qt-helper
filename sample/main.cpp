#include "mainwindow.h"
#include "oneinstanceapp.h"
#include "proxystyle.h"

int main(int argc, char *argv[])
{
    OneInstanceApp app(argc, argv);

    app.setStyle(new QProxyStyle("Fusion"));

    MainWindow win;
    win.show();

    return app.exec("~instance");
}
