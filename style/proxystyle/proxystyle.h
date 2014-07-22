#ifndef PROXYSTYLE_H
#define PROXYSTYLE_H

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
