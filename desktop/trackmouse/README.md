Usage

```cpp
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tm = new TrackMouse(this);
    tm->setDelay(1000); // Set delay (default is 100 ms)
    QObject::connect(tm, SIGNAL(mousePos(QPoint)), this, SLOT(capture(QPoint)));
    tm->start();
}
```
