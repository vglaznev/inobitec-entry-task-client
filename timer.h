#ifndef TIMER_H
#define TIMER_H

#include <QObject>

class QElapsedTimer;

class Timer : public QObject
{
    Q_OBJECT
public:
    explicit Timer(QObject *parent = nullptr);
    ~Timer();

    qreal stop();

public slots:
    void start();

private:
    QElapsedTimer *timer;
};

#endif
