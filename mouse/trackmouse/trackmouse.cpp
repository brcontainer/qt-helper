/*
 * qt-helper
 *
 * Copyright (c) 2018 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include "trackmouse.h"
#include <QCursor>

TrackMouse::TrackMouse(QObject *parent) :
    QThread(parent),
    delay(10),
    track(false),
    running(true),
    lastPosActive(false),
    byWidget(0),
    limitWidget(false)
{
}

void TrackMouse::enable(const bool enable) {
    track = enable;
}

void TrackMouse::detectMove(const bool enable) {
    lastPosActive = enable;
}

void TrackMouse::setDelay(const int value) {
    delay = value;
}

void TrackMouse::setWidget(QWidget *widget, bool limit) {
    byWidget = widget;
    limitWidget = limit;
}

void TrackMouse::run(void) {
    QPoint lastPos;
    QPoint currentPost;

    while (running) {
        QThread::msleep(delay);
        currentPost = cursorPosition();

        if (
            track == true && //If TrackMouse::enable(true)
            (lastPosActive == false || lastPos != currentPost) && //If TrackMouse::detectMove(true)
            (limitWidget == false || (
                 currentPost.x() > -1 &&
                 currentPost.y() > -1 &&
                 currentPost.x() <= byWidget->width() &&
                 currentPost.y() <= byWidget->height()
            )) //If TrackMouse::setWidget(widget, true)
        ) {
            lastPos = currentPost;
            emit mousePos(currentPost);
        }
    }
}

void TrackMouse::end() {
    running = false;
    wait();
    terminate();
}

QPoint TrackMouse::cursorPosition() {
    if (byWidget == 0) {
        return QCursor::pos();
    }

    return byWidget->mapFromGlobal(QCursor::pos());
}
