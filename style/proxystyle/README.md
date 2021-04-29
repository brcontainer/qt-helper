`QComboBox` pop-up does not expand the content. Pop-ups are limited by the size of `QComboBox`, this problem can be circumvented if you create a custom combobox like:

```
class customCombo: QComboBox { ... }
```

But it is not possible to customize the native combobox (eg in `QWebViews`).
This class fix the problem by making the native combobox work in a better way.

See image "without" class:

![combobox/popup-menu without class](http://s7.postimg.org/5oehsmo07/image.png)

See image with class:

![combobox/popup-menu with class](http://s29.postimg.org/62q7dlm2v/image.png)

Usage:

```cpp
#include "mainwindow.h"
#include "proxystyle.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setStyle(new ProxyStyle);

    return a.exec();
}
```
