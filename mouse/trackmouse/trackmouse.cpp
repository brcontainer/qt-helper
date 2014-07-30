/*
qt-helper 0.0.1
Copyright (c) 2014 Guilherme Nascimento (brcontainer@yahoo.com.br)

Released under the MIT license
*/

#include "trackmouse.h"
#include <QCursor>

trackMouse::trackMouse(QObject *parent) :
    QThread(parent),
    delay(10),
    track(false),
    running(true),
    lastPosActive(false),
    byWidget(0),
    limitWidget(false)
{
}

void trackMouse::enable(const bool enable) {
    track = enable;
}

void trackMouse::detectMove(const bool enable) {
    lastPosActive = enable;
}

void trackMouse::setDelay(const int value) {
    delay = value;
}

void trackMouse::setWidget(QWidget *widget, bool limit) {
    byWidget = widget;
    limitWidget = limit;
}

void trackMouse::run(void) {
    QPoint lastPos;
    QPoint currentPost;

    while(running) {
        QThread::msleep(delay);
        currentPost = cursorPosition();

        if (
            track == true && //If trackMouse::enable(true)
            (lastPosActive == false || lastPos != currentPost) && //If trackMouse::detectMove(true)
            (limitWidget == false || (
                 currentPost.x() > -1 &&
                 currentPost.y() > -1 &&
                 currentPost.x() <= byWidget->width() &&
                 currentPost.y() <= byWidget->height()
            )) //If trackMouse::setWidget(widget, true)
        ) {
            lastPos = currentPost;
            emit mousePos(currentPost);
        }
    }
}

void trackMouse::end() {
    running = false;
    wait();
    terminate();
}

QPoint trackMouse::cursorPosition() {
    if (byWidget == 0) {
        return QCursor::pos();
    } else {
        return byWidget->mapFromGlobal(QCursor::pos());
    }
}
