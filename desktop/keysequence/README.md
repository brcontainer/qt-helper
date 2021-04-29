Usage:

```cpp
#include "keysequence.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    KeySequence::widget(this, "Ctrl+w", this, SLOT(close()));
    KeySequence::widget(this, "Ctrl+w", this, SLOT(close()));
}
```
