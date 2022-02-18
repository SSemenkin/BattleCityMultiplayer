#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "game.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(Game *instance, QObject *parent = nullptr);
    bool startServer();

protected:
    virtual void onNewConnection();
    virtual void onClientDisconnected();
    virtual void onConnectionError(QTcpSocket::SocketError error);
    virtual void onClientReadyRead();
    virtual void notificateAll(Socket *sender, const QByteArray &message);
    void checkIsPacketFull(Socket *socket);
    void messageReceived(Socket*, const QByteArray&);
private:
    QList<Socket*> m_clients;
    QHash<Socket*, QByteArray> m_received;
    QHash<Socket*, uint64_t> m_bufferSize;
    Game *m_gameInstance;
};

#endif // SERVER_H
