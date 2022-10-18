#include "timer.h"

#include <QElapsedTimer>

Timer::Timer(QObject *parent) : QObject(parent)
{
    timer = new QElapsedTimer();
}

void Timer::start() {
    timer->start();
}

qreal Timer::stop() {
    return static_cast<qreal>(timer->elapsed()) / 1000;
}
