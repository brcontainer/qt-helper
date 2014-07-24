This class is for you to use if you need your application to open only once (usually in desktop system you can open several times the same application).

Usage:

```
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QString tmpFolder = QDir::toNativeSeparators(QDir::tempPath() + "process");

	if (runProcess::test(global::userPath + "process")) {
		runProcess *rp = new runProcess(this); //Set window in parent process
		rp->setup(tmpFolder); //Setup folder

		QObject::connect(rp, SIGNAL(alreadyRunning()), win, SLOT(quitApp()));
		rp->start();
	} else {
		quitApp();
	}
}

void MainWindow::quitApp() {
	qApp->quit();
}
```
