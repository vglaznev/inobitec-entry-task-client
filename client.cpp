#include "client.h"
#include "timer.h"

#include <QTcpSocket>
#include <QDataStream>

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connectionTimer = new Timer(this);

    connect(socket, &QTcpSocket::readyRead, this, &Client::readData);
    connect(socket, &QTcpSocket::connected, this, &Client::connected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected);

    connect(socket, &QTcpSocket::connected, connectionTimer, &Timer::start);
}

Client::~Client(){

}

bool Client::connectToServer(QString host, quint16 port){
    socket->connectToHost(host, port);

    if(!socket->waitForConnected(5000)){
        emit connectionFailed();
        return false;
    }
    return true;
}

void Client::disconnectFromServer(){
    //socket->disconnectFromHost();
   socket->close();
}

void Client::readData(){
    QDataStream stream(socket);

    qreal value;
    stream >> value;

    emit newDataArrived(connectionTimer->stop(), value);
}
