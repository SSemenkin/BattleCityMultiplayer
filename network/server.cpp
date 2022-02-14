#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    connect(this, &QTcpServer::newConnection, this, &Server::onNewConnection);
    connect(this, &QTcpServer::acceptError, this, &Server::onConnectionError);
    connect(this, &Server::messageReceived, this, &Server::notificateAll);
}

bool Server::startServer()
{
    return listen(QHostAddress::LocalHost, 55368);
}

void Server::onNewConnection()
{
    while(hasPendingConnections()) {
        Socket *socket = static_cast<Socket*>(nextPendingConnection());
        m_clients.push_back(socket);

        connect(socket, &Socket::readyRead, this, &Server::onClientReadyRead);
        connect(socket, &Socket::disconnected, this, &Server::onClientDisconnected);
    }
}

void Server::onClientDisconnected()
{
    if (Socket *socket = static_cast<Socket*>(sender())) {
        m_clients.removeOne(socket);
        m_received.remove(socket);
        socket->deleteLater();
    }
}

void Server::onConnectionError(QAbstractSocket::SocketError error)
{
    qDebug() << "Ошибка при подключении к серверу: " << error;
}

void Server::onClientReadyRead()
{
    if (Socket *socket = static_cast<Socket*>(sender())) {
        QByteArray &buffer = m_received[socket];
        buffer.append(socket->readAll());

        while(true) {
            int endIndex = buffer.indexOf(FINISH_TOKEN);
            if (endIndex == -1) {
                break;
            }

            QString message = QString::fromUtf8(buffer.left(endIndex));
            buffer.remove(0, endIndex + 1);
            emit messageReceived(socket, message);
        }
    }
}

void Server::notificateAll(Socket *except, const QString &message)
{
    for (int i = 0; i < m_clients.size(); ++i) {
        if (except != m_clients[i]) {
            m_clients[i]->write(message.toUtf8() + FINISH_TOKEN);
        }
    }
}
