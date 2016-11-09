This class is for you to use if you need your application to open only once (usually in desktop system you can open several times the same application).

Usage:

```cpp
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    SingleInstance *si = new SingleInstance(this);

    si->file("C:/DATA/test"); //Session file used for detect multiple instances

    //Application allready running
    QObject::connect(si, SIGNAL(alreadyRunning()), this, SLOT(quit()));

    //Faild to write session file
    QObject::connect(si, SIGNAL(notPerformed()), this, SLOT(quit()));

    si->start();
}

void MainWindow::quitApp() {
	qApp->quit();
}
```
