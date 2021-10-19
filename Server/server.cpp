#include "server.h"
#include <QHostAddress>
#include <QNetworkInterface>
#include <iostream>

Server::Server(QObject *parent) : QTcpServer(parent)
{
    const QHostAddress localHost = QHostAddress(QHostAddress::LocalHost);

    const QList<QHostAddress> adresses = QNetworkInterface::allAddresses();


    qDebug() <<  "Choose server adress:";

    int counter = 1;
    for (int i = 0; i < adresses.size(); ++i) {
        if (adresses.at(i).protocol() == QAbstractSocket::IPv4Protocol &&
                adresses.at(i) != localHost) {
            qDebug().nospace() << counter++ << "." << adresses.at(i).toString();
        }
    }

    int choice, port;
    validInput(choice);
    assert ((choice < counter && choice > -1) && "You must enter valid hostadress number.");


    qDebug() << "Enter server port:";
    validInput(port);

    system("cls");

    if (listen(adresses.at(choice - 1), port)) {
        qDebug() << "server started successfully.";
    } else {
        qDebug() << "failed to start server.";
    }
}

void Server::incomingConnection(qintptr id)
{
    qDebug() << "Client " << id << " connected";

    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(id);

    connect(socket, &QTcpSocket::readyRead, this, &Server::newMessageFromClient);
    connect(socket, &QTcpSocket::disconnected, this, &Server::clientDisconnected);


    m_clients.push_back(socket);
}

void Server::clientDisconnected()
{
    QTcpSocket *disconnected = qobject_cast<QTcpSocket*> (sender());

    int disconnectedIndex = m_clients.indexOf(disconnected);
    if  (disconnectedIndex == -1) {
        qDebug() << "socket with descriptor " << disconnected->socketDescriptor() << " does not belong to server.";
        return;
    } else {
        m_clients.removeAt(disconnectedIndex);
        disconnected->deleteLater();
    }
}

void Server::newMessageFromClient()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    QString reply = socket->readAll();

    auto iterator = m_buffers.find(socket);
    if (iterator != m_buffers.end()) {
        reply = *iterator + reply;
    }

    QString handledReply = reply.left(reply.lastIndexOf(finishToken));

    if (handledReply.length() != reply.length()) {
        m_buffers[socket].append(reply.rightRef(reply.length() - handledReply.length()));
    }


}
