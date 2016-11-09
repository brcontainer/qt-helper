/*
 * qt-helper
 *
 * Copyright (c) 2016 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "keysequence.h"
#include <QObject>
#include <QAction>

QAction *KeySequence::widget(QWidget *widget, const QString &sequence, const QObject *receiver,
                         const char *member, const bool portableText)
{
    QKeySequence seq;

    if (portableText) {
        seq = QKeySequence(sequence, QKeySequence::PortableText);
    } else {
        seq = QKeySequence(sequence);
    }

    return KeySequence::widget(widget, seq, receiver, member);
}

QAction *KeySequence::widget(QWidget *widget, const QKeySequence &shortcut, const QObject *receiver,
                         const char *member)
{
    QAction *a = KeySequence::action(widget, receiver, member);
    a->setShortcut(shortcut);
    return a;
}

QAction *KeySequence::widget(QWidget *widget, const QList<QKeySequence> &shortcuts,
                         const QObject *receiver, const char *member)
{
    QAction *a = KeySequence::action(widget, receiver, member);
    a->setShortcuts(shortcuts);
    return a;
}

QAction *KeySequence::widget(QWidget *widget, QKeySequence::StandardKey standardkey,
                         const QObject *receiver, const char *member)
{
    QAction *a = KeySequence::action(widget, receiver, member);
    a->setShortcuts(standardkey);
    return a;
}

QAction *KeySequence::widget(QWidget *widget, Qt::ShortcutContext context, const QObject *receiver,
                         const char *member)
{
    QAction *a = KeySequence::action(widget, receiver, member);
    a->setShortcutContext(context);
    return a;
}

QAction *KeySequence::action(QWidget *widget, const QObject *receiver, const char *member)
{
    QAction *act = new QAction(widget);
    QObject::connect(act, SIGNAL(triggered()), receiver, member);
    widget->addAction(act);
    return act;
}
