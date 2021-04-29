Prevent freeze (or crash) apps with `QDesktopServices::openUrl`

Usage:

```cpp
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    // Open default file manager ("explorer" in Windows and "Finder" in MacOS)
	OpenExternal::local("C:");

    // Try open with default program, if failed try use OpenExternal::showInFolder
    OpenExternal::local("C:/foder/file.txt");

    /*
     * Open default file manager:
     * like this `explorer /select,C:\file.txt` in Windows
     * like this `open -R /home/file.txt` in Mac
     * if failed try only open folder
     */
	OpenExternal::showInFolder("C:/foder/file.txt");

    // Open default web-browser
	OpenExternal::url("http://github.com");
}
```
