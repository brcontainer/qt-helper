Usage

```
    ui->setupUi(this);
    tt = new trackMouse(this);
    tt->setDelay(1000); // Set delay (default is 100 ms)
    QObject::connect(tt, SIGNAL(mousePos(QPoint)), this, SLOT(capture(QPoint)));
    tt->start();
```
