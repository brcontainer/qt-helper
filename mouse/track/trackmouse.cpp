#include "trackmouse.h"
#include <QCursor>
#include <QDebug>

trackMouse::trackMouse(QObject *parent) :
    QThread(parent),
    delay(100),
    track(false),
    running(true)
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

void trackMouse::setDelay(const int value) {
    delay = value;
}

void trackMouse::run() {
    while(running) {
        QThread::msleep(delay);
        if (track == true) {
            emit mousePos(QCursor::pos());
        }
    }
}
