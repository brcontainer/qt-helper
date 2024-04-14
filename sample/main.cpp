#include "mainwindow.h"
#include "oneinstanceapp.h"
#include "proxystyle.h"

int main(int argc, char *argv[])
{
    OneInstanceApp app("instance", argc, argv);

    app.setStyle(new ProxyStyle("WindowsVista"));

    MainWindow win;
    win.show();

    return app.exec();
}
