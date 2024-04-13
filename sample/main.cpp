#include "mainwindow.h"
#include "oneinstanceapp.h"
#include "proxystyle.h"

#include <QMessageBox>

int main(int argc, char *argv[])
{
    OneInstanceApp app("instance", argc, argv);

    app.setStyle(new ProxyStyle("Fusion"));

    MainWindow win;
    win.show();

    return app.exec();
}
