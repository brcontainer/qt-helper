#ifndef PROXYSTYLE_H
#define PROXYSTYLE_H

/*
qt-helper 0.0.1
Copyright (c) 2014 Guilherme Nascimento (brcontainer@yahoo.com.br)

Released under the MIT license
*/

#include <QProxyStyle>

class proxyStyle : public QProxyStyle
{
    Q_OBJECT
public:
    proxyStyle(QStyle *style = 0);
    proxyStyle(const QString &key);
    int styleHint(StyleHint hint, const QStyleOption *option = 0, const QWidget *widget = 0, QStyleHintReturn *returnData = 0) const;
};

#endif // PROXYSTYLE_H
