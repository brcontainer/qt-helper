/*
 * qt-helper
 *
 * Copyright (c) 2018 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "proxystyle.h"
#include <QAbstractItemView>
#include <QComboBox>

ProxyStyle::ProxyStyle(QStyle *style) :
    QProxyStyle(style)
{
}

ProxyStyle::ProxyStyle(const QString &key) :
    QProxyStyle(key)
{
}

int ProxyStyle::styleHint(StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    if (hint == QStyle::SH_ComboBox_Popup) {
        //convert qwidget in QComboBox
        const QComboBox *combo = (QComboBox *) widget;
        const QObjectList a = combo->children();
        const int j = a.count();
        QAbstractItemView *view = 0;
        QString className = "";
        bool hasView = false;
        int i;

        /*
        at this point I have not used combo->view() because he "crash" the application without explanation
        so I had to make a loop to find the "view"
        */
        for (i = 0; i < j; ++i) {
            const QObjectList b = a.at(i)->children();
            const int y = b.count();

            for (int x = 0; x < y; ++x) {
                className = b.at(x)->metaObject()->className();
                if (className == "QComboBoxListView") {
                    view = (QAbstractItemView *) b.at(x);
                    hasView = true;
                    break;
                }
            }

            if (hasView) {
                break;
            }
        }

        if (hasView) {
            const int iconSize = combo->iconSize().width();
            const QFontMetrics fontMetrics1 = view->fontMetrics();
            const QFontMetrics fontMetrics2 = combo->fontMetrics();
            const int z = combo->count();
            int lastWidth = combo->width(); //default width

            for (i = 0; i < z; ++i) {
                const int textWidth = qMax(
                    fontMetrics1.width(combo->itemText(i) + "WW"),
                    fontMetrics2.width(combo->itemText(i) + "WW")
                );

                if (combo->itemIcon(i).isNull()) {
                    lastWidth = qMax(lastWidth, textWidth);
                } else {
                    lastWidth = qMax(lastWidth, textWidth + iconSize);
                }
            }

            view->setFixedWidth(lastWidth);
        }
    }

    return QProxyStyle::styleHint(hint, option, widget, returnData);
}
