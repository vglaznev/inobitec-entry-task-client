#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class QTcpSocket;
class Timer;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void readData();

signals:
    void newDataArrived(qreal, qreal);
    void connected();
    void disconnected();
    void connectionFailed();

public slots:
    bool connectToServer(QString, quint16);
    void disconnectFromServer();

private:
    QTcpSocket *socket;
    Timer *connectionTimer;
};

#endif
