/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "shortcut.h"
#include <QAction>
#include <QKeySequence>
#include <QObject>

QAction *Shortcut::bind(QWidget *widget, const QObject *receiver, const char *member)
{
    QAction *action = new QAction(widget);
    QObject::connect(action, SIGNAL(triggered()), receiver, member);
    widget->addAction(action);
    return action;
}

QAction *Shortcut::keys(QWidget *widget, const QKeySequence &shortcut,
    const QObject *receiver, const char *member)
{
    QAction *action = Shortcut::bind(widget, receiver, member);
    action->setShortcut(shortcut);
    return action;
}

QAction *Shortcut::keys(QWidget *widget, const QString &sequence,
    const QObject *receiver, const char *member, const bool portableText)
{
    QKeySequence seq;

    if (portableText) {
        seq = QKeySequence(sequence, QKeySequence::PortableText);
    } else {
        seq = QKeySequence(sequence, QKeySequence::NativeText);
    }

    return Shortcut::keys(widget, seq, receiver, member);
}

QAction *Shortcut::keys(QWidget *widget, const QList<QKeySequence> &shortcuts,
    const QObject *receiver, const char *member)
{
    QAction *action = Shortcut::bind(widget, receiver, member);
    action->setShortcuts(shortcuts);
    return action;
}

QAction *Shortcut::keys(QWidget *widget, QKeySequence::StandardKey standardkey,
    const QObject *receiver, const char *member)
{
    QAction *action = Shortcut::bind(widget, receiver, member);
    action->setShortcuts(standardkey);
    return action;
}
