/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
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

int ProxyStyle::styleHint(StyleHint hint, const QStyleOption *option,
                            const QWidget *widget, QStyleHintReturn *returnData) const
{
    if (hint == QStyle::SH_ComboBox_Popup) {
        // Convert QWidget in QComboBox
        const QComboBox *combo = (QComboBox *) widget;
        const QObjectList list = combo->children();

        QAbstractItemView *view = 0;
        bool hasView = false;
        int i;
        int j = list.count();

        /*
        At this point I have not used combo->view() because he "crash" the application
        without explanation so I had to make a loop to find the "view"
        */
        QString name;

        for (i = 0; i < j; ++i) {
            const QObjectList subList = list.at(i)->children();
            const int y = subList.count();

            for (int x = 0; x < y; ++x) {
                const QObject *ref = subList.at(x);
                name = ref->metaObject()->className();

                if (name == "QComboBoxListView") {
                    view = (QAbstractItemView *) ref;
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
            int lastWidth = combo->width(); // default width

            const QFontMetrics metrics1 = view->fontMetrics();
            const QFontMetrics metrics2 = combo->fontMetrics();

            j = combo->count();

            for (i = 0; i < j; ++i) {
//                const int textWidth = qMax(
//                    metrics1.width(combo->itemText(i) + "WW"),
//                    metrics2.width(combo->itemText(i) + "WW")
//                );

                const int textWidth = getSize(metrics1, metrics2, combo->itemText(i));

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

int ProxyStyle::getSize(const QFontMetrics &a, const QFontMetrics &b, const QString &text) const
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
    return qMax(a.horizontalAdvance(text + "WW"), b.horizontalAdvance(text + "WW"));
#else
    return qMax(a.width(text + "WW"), b.width(text + "WW"));
#endif
}
