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

    int levelId() const;
    void setLevelId(int levelId);

protected:
    void incomingConnection(qintptr handle) override;
private:
    QList<QTcpSocket*> m_clients;
    int m_levelId;
private:
    void receiveMessageFromClient();
};

#endif // GAMESERVER_H
