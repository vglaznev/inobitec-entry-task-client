#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QPointF>

class QTcpSocket;
class Timer;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    virtual ~Client();

    void readData();

signals:
    void newDataArrived(QPointF);
    void connected();
    void disconnected();

public slots:
    bool connectToServer(QString, quint16);
    void disconnectFromServer();

private:
    QTcpSocket* socket;
    Timer* timer;
};

#endif // CLIENT_H
