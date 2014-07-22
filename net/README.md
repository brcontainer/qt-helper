Usage:

```
    net = new netWork;
    net->setCookieJar(new QNetworkCookieJar);
    net->setCache(new QNetworkDiskCache);

    QWebPage *page = ui->webView->page();//or new QWebView->page(); or new QWebPage();
    page->setNetworkAccessManager(net);
```
