#ifndef ACTION_H
#define ACTION_H

/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QKeySequence>

class QAction;
class QWidget;

class Action
{

public:
    static QAction *widget(QWidget *widget, const QString &sequence, const QObject *receiver,
                            const char *member, const bool portableText = false);

    static QAction *widget(QWidget *widget, const QKeySequence &shortcut,
                            const QObject *receiver, const char *member);

    static QAction *widget(QWidget *widget, const QList<QKeySequence> &shortcuts,
                            const QObject *receiver, const char *member);

    static QAction *widget(QWidget *widget, QKeySequence::StandardKey standardkey,
                            const QObject *receiver, const char *member);

    static QAction *widget(QWidget *widget, Qt::ShortcutContext context, const QObject *receiver,
                            const char *member);

    static QAction *bind(QWidget *widget, const QObject *receiver, const char *member);
};

#endif // ACTION_H
