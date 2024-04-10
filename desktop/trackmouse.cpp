/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "trackmouse.h"
#include <QCursor>

TrackMouse::TrackMouse(QObject *parent) :
    QObject(parent),
    lastPosActive(false),
    byWidget(0),
    limitWidget(false)
{
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
}

TrackMouse::~TrackMouse()
{
    enable(false);
    timer = 0;
}

void TrackMouse::enable(const bool enable)
{
    if (enable) {
        timer->start();
    } else {
        timer->stop();
    }
}

void TrackMouse::detectMove(const bool enable)
{
    lastPosActive = enable;
}

void TrackMouse::setDelay(const int value)
{
    timer->setInterval(value);
}

void TrackMouse::setWidget(QWidget *widget, bool limit)
{
    byWidget = widget;
    limitWidget = limit;
}

void TrackMouse::refresh()
{
    const QPoint current = cursorPosition();

    if (
        // If detectMove(false) or detectMove(true)
        (lastPosActive == false || lastPos != current) &&

        // If setWidget(widget, false) or setWidget(widget, true)
        (limitWidget == false || (
             current.x() > -1 &&
             current.y() > -1 &&
             current.x() <= byWidget->width() &&
             current.y() <= byWidget->height()
        ))
    ) {
        lastPos = current;
        emit position(current);
    }
}

QPoint TrackMouse::cursorPosition() const
{
    if (byWidget == 0) {
        return QCursor::pos();
    }

    return byWidget->mapFromGlobal(QCursor::pos());
}
