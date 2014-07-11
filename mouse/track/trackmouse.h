#ifndef TRACKMOUSE_H
#define TRACKMOUSE_H

#include <QThread>
#include <QPoint>

class trackMouse : public QThread
{
    Q_OBJECT
public:
    explicit trackMouse(QObject *parent = 0);
    void enable(const bool enable = true);
    void setDelay(const int value);
    void end();

protected:
    virtual void run();

private:
    int delay;
    bool track;
    bool running;

signals:
    void mousePos(const QPoint pos);
};

#endif // TRACKMOUSE_H
