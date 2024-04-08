/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "action.h"
#include <QObject>
#include <QAction>

QAction *Action::widget(QWidget *widget, const QString &sequence,
    const QObject *receiver, const char *member, const bool portableText)
{
    QKeySequence seq;

    if (portableText) {
        seq = QKeySequence(sequence, QKeySequence::PortableText);
    } else {
        seq = QKeySequence(sequence);
    }

    return Action::widget(widget, seq, receiver, member);
}

QAction *Action::widget(QWidget *widget, const QKeySequence &shortcut,
    const QObject *receiver, const char *member)
{
    QAction *action = Action::bind(widget, receiver, member);
    action->setShortcut(shortcut);
    return action;
}

QAction *Action::widget(QWidget *widget, const QList<QKeySequence> &shortcuts,
    const QObject *receiver, const char *member)
{
    QAction *action = Action::bind(widget, receiver, member);
    action->setShortcuts(shortcuts);
    return action;
}

QAction *Action::widget(QWidget *widget, QKeySequence::StandardKey standardkey,
    const QObject *receiver, const char *member)
{
    QAction *action = Action::bind(widget, receiver, member);
    action->setShortcuts(standardkey);
    return action;
}

QAction *Action::widget(QWidget *widget, Qt::ShortcutContext context,
    const QObject *receiver, const char *member)
{
    QAction *action = Action::bind(widget, receiver, member);
    action->setShortcutContext(context);
    return action;
}

QAction *Action::bind(QWidget *widget, const QObject *receiver, const char *member)
{
    QAction *action = new QAction(widget);
    QObject::connect(action, SIGNAL(triggered()), receiver, member);
    widget->addAction(action);
    return action;
}
