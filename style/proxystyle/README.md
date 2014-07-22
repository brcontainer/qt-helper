```cpp
#include "mainwindow.h"
#include "proxystyle.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setStyle(new proxyStyle); //Set proxyStyle

    return a.exec();
}
```
