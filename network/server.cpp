#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    connect(this, &QTcpServer::newConnection, this, &Server::onNewConnection);
    connect(this, &QTcpServer::acceptError, this, &Server::onConnectionError);
}

bool Server::startServer()
{

}

void Server::onNewConnection()
{
    while(Socket *socket = static_cast<Socket*>(nextPendingConnection())) {
        m_clients.push_back(socket);

        connect(socket, &Socket::readyRead, this, &Server::onClientReadyRead);
        connect(socket, &Socket::disconnected, this, &Server::onClientDisconnected);
    }
}

void Server::onClientDisconnected()
{
    if (Socket *socket = static_cast<Socket*>(sender())) {
        m_clients.removeOne(socket);
    }
}

void Server::onConnectionError(QAbstractSocket::SocketError error)
{
    qDebug() << "Ошибка при подключении к серверу: " << error;
}

void Server::onClientReadyRead()
{

}
