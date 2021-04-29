This class fix problems with "Response unknown" that occurs with some servers

Usage:

```cpp
net = new Network;
net->setCookieJar(new QNetworkCookieJar);
net->setCache(new QNetworkDiskCache);

QWebPage *page = ui->webView->page();//or new QWebView->page(); or new QWebPage();
page->setNetworkAccessManager(net);
```
