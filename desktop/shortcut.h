#ifndef SHORTCUT_H
#define SHORTCUT_H

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

class Shortcut
{

public:
    static QAction *bind(QWidget *widget, const QObject *receiver, const char *member);

    static QAction *keys(QWidget *widget, const QKeySequence &shortcut,
                            const QObject *receiver, const char *member);

    static QAction *keys(QWidget *widget, const QString &sequence, const QObject *receiver,
                            const char *member, const bool portableText = false);

    static QAction *keys(QWidget *widget, const QList<QKeySequence> &shortcuts,
                            const QObject *receiver, const char *member);

    static QAction *keys(QWidget *widget, QKeySequence::StandardKey standardkey,
                            const QObject *receiver, const char *member);

    static QAction *context(QWidget *widget, Qt::ShortcutContext context, const QObject *receiver,
                            const char *member);
};

#endif // SHORTCUT_H
