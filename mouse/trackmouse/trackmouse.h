#ifndef TRACKMOUSE_H
#define TRACKMOUSE_H

/*
 * qt-helper
 *
 * Copyright (c) 2018 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QThread>
#include <QPoint>
#include <QWidget>

class TrackMouse : public QThread
{
    Q_OBJECT
public:
    explicit TrackMouse(QObject *parent = 0);
    void enable(const bool enable = true);
    void detectMove(const bool enable = true);
    void setDelay(const int value);
    void setWidget(QWidget *widget = 0, bool limit = false);
    void end();
    QPoint cursorPosition();

protected:
    virtual void run(void);

private:
    int delay;
    bool track;
    bool running;
    bool lastPosActive;
    QWidget *byWidget;
    bool limitWidget;

signals:
    void mousePos(const QPoint pos);
};

#endif // TRACKMOUSE_H
