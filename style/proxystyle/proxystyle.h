#ifndef PROXYSTYLE_H
#define PROXYSTYLE_H

/*
 * qt-helper
 *
 * Copyright (c) 2021 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QProxyStyle>

class ProxyStyle : public QProxyStyle
{
    Q_OBJECT

public:
    ProxyStyle(QStyle *style = 0);
    ProxyStyle(const QString &key);

    int styleHint(StyleHint hint, const QStyleOption *option = 0,
            const QWidget *widget = 0, QStyleHintReturn *returnData = 0) const;
};

#endif // PROXYSTYLE_H
