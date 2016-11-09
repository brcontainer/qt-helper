#ifndef KEYSEQ_H
#define KEYSEQ_H

/*
 * qt-helper
 *
 * Copyright (c) 2016 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QKeySequence>

class QWidget;
class QObject;
class QAction;

class KeySequence
{

public:
    static QAction *widget(QWidget *widget, const QString &sequence, const QObject *receiver,
                            const char *member, const bool portableText = false);

    static QAction *widget(QWidget *widget, const QKeySequence &shortcut, const QObject *receiver,
                            const char *member);

    static QAction *widget(QWidget *widget, const QList<QKeySequence> &shortcuts,
                            const QObject *receiver, const char *member);

    static QAction *widget(QWidget *widget, QKeySequence::StandardKey, const QObject *receiver,
                            const char *member);

    static QAction *widget(QWidget *widget, Qt::ShortcutContext context, const QObject *receiver,
                            const char *member);

    static QAction *action(QWidget *widget, const QObject *receiver, const char *member);
};

#endif // KEYSEQ_H
