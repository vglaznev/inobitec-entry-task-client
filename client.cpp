#include "client.h"

#include <QTcpSocket>
#include <QDataStream>
#include "timer.h"

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    timer = new Timer(this);

    connect(socket, &QTcpSocket::readyRead, this, &Client::readData);
    connect(socket, &QTcpSocket::connected, [this](){emit connected();});
    connect(socket, &QTcpSocket::disconnected, [this](){emit disconnected();});

    connect(socket, &QTcpSocket::connected, timer, &Timer::start);
    //connect(socket, &QTcpSocket::readyRead, timer, &Timer::stop);
}

Client::~Client(){

}

bool Client::connectToServer(QString host, quint16 port){
    socket->connectToHost(host, port);

    connect(socket, &QTcpSocket::disconnected, [this](){
        socket->deleteLater();
    });

    return socket->waitForConnected(5000);
}

void Client::disconnectFromServer(){
    socket->close();
}

void Client::readData(){
    QDataStream stream(socket);
    stream.startTransaction();
    qreal value;
    stream >> value;
    stream.commitTransaction();
    emit newDataArrived(QPointF(timer->stop(), value));
}
