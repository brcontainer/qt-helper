#include "trackmouse.h"
#include <QCursor>
#include <QDebug>

trackMouse::trackMouse(QObject *parent) :
    QThread(parent),
    delay(10),
    track(false),
    running(true),
    lastPosActive(false)
{
}

void trackMouse::end() {
    running = false;
    wait();
    terminate();
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

void trackMouse::run() {
    QPoint lastPos;
    QPoint currentPost;

    while(running) {
        QThread::msleep(delay);
        currentPost = QCursor::pos();
        if (track == true && (lastPosActive == false || lastPos != currentPost)) {
            lastPos = currentPost;
            emit mousePos(currentPost);
        }
    }
}
