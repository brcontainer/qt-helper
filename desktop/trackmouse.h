#ifndef TRACKMOUSE_H
#define TRACKMOUSE_H

/*
 * QtHelper
 *
 * Copyright (c) 2024 Guilherme Nascimento (brcontainer@yahoo.com.br)
 *
 * Released under the MIT license
 */

#include <QTimer>
#include <QPoint>
#include <QWidget>

class TrackMouse : public QObject
{
    Q_OBJECT

public:
    explicit TrackMouse(QObject *parent = 0);
    ~TrackMouse();
    void enable(const bool enable = true);
    void detectMove(const bool enable = true);
    void setDelay(const int value);
    void setWidget(QWidget *widget = 0, bool limit = false);
    void end();

private:
    bool lastPosActive;
    QWidget *byWidget;
    bool limitWidget;
    QTimer *timer;
    QPoint lastPos;
    QPoint cursorPosition() const;

signals:
    void position(const QPoint &pos);

public slots:
    void refresh();
};

#endif // TRACKMOUSE_H
