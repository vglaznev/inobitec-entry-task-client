#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <memory>

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
    std::unique_ptr<QElapsedTimer> timer;
};

#endif
