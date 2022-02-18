#include "server.h"
#include <QDataStream>
#include "network/message.h"

Server::Server(Game* instance, QObject *parent) : QTcpServer(parent),
    m_gameInstance(instance)
{
    connect(this, &QTcpServer::newConnection, this, &Server::onNewConnection);
    connect(this, &QTcpServer::acceptError, this, &Server::onConnectionError);
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
    Socket *socket = qobject_cast<Socket*>(sender());
    if (!socket) {
        return;
    }

    if (m_bufferSize[socket] == 0) {
        if (socket->bytesAvailable() >= sizeof(uint64_t)) {
            m_bufferSize[socket] = (uint64_t)socket->read(sizeof (uint64_t)).toInt();
            checkIsPacketFull(socket);
        }
    } else {
        checkIsPacketFull(socket);
    }
//    if (Socket *socket = static_cast<Socket*>(sender())) {
//        QByteArray &buffer = m_received[socket];
//        buffer.append(socket->readAll());

//        while(true) {
//            int endIndex = buffer.indexOf(FINISH_TOKEN);
//            if (endIndex == -1) {
//                break;
//            }

//            QString message = QString::fromUtf8(buffer.left(endIndex));
//            buffer.remove(0, endIndex + 1);
//            emit messageReceived(socket, message);
//        }
//    }
}

void Server::notificateAll(Socket *except, const QByteArray &message)
{
    QDataStream dataStream;
    for (int i = 0; i < m_clients.size(); ++i) {
        if (except != m_clients[i]) {
            dataStream.setDevice(m_clients[i]);
            dataStream << (uint64_t) message.size() << message;
        }
    }
}

void Server::checkIsPacketFull(Socket *socket)
{
    m_received[socket].append(socket->readAll());

    if ((uint64_t)m_received[socket].size() >= m_bufferSize[socket]) {
        QByteArray message = m_received[socket].left(m_bufferSize[socket]);
        m_received[socket] = m_received[socket].right(m_received.size() - m_bufferSize[socket]);
        messageReceived(socket, message);
        m_bufferSize[socket] = 0;
    }
}

void Server::messageReceived(Socket *socket, const QByteArray &data)
{
    Message message(data);

    switch(message.type()) {
        case Message::Type::RequestChangePosition:
            break;
        case Message::Type::RequestFire:
            break;
        case Message::Type::RequestStartPosition:
            break;
    }
}
