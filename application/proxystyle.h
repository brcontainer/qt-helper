#ifndef PROXYSTYLE_H
#define PROXYSTYLE_H

/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QProxyStyle>
#include <QString>

class ProxyStyle : public QProxyStyle
{
    Q_OBJECT

public:
    ProxyStyle(QStyle *style = 0);
    ProxyStyle(const QString &key);
    int styleHint(StyleHint hint, const QStyleOption *option = 0,
                  const QWidget *widget = 0, QStyleHintReturn *returnData = 0) const;

private:
    int getSize(const QFontMetrics &a,
                const QFontMetrics &b, const QString &text) const;
};

#endif // PROXYSTYLE_H
