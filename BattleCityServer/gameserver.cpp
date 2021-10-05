#include "gameserver.h"

GameServer::GameServer(QObject *parent) : QTcpServer(parent)
{

}

int GameServer::levelId() const
{
    return m_levelId;
}

void GameServer::setLevelId(int levelId)
{
    m_levelId = levelId;
}

void GameServer::incomingConnection(qintptr handle)
{
    qDebug() << "New client is connected. Handle " << handle;

    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(handle);

    QObject::connect(client, &QTcpSocket::readyRead, this, &GameServer::receiveMessageFromClient);

    m_clients.append(client);
    client->write(QString::number(levelId()).toLatin1());
}

void GameServer::receiveMessageFromClient()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    ClientEventType event = static_cast<ClientEventType>(QString(socket->read(1)).toInt());

    qDebug() << static_cast<int>(event);
}
