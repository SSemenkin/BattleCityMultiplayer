#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QTcpServer>
#include <QTcpSocket>


class GameServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = nullptr);

    enum class ClientEventType {
        Move,
        Fire
    };


protected:
    void incomingConnection(qintptr handle) override;
private:
    QList<QTcpSocket*> m_clients;
private:
    void receiveMessageFromClient();
};

#endif // GAMESERVER_H
