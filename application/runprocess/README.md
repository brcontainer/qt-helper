```
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QString tmpFolder = QDir::tempPath() + "process";

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
