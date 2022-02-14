#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <network/socket.h>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    bool startServer();
signals:
    void messageReceived(Socket *sender, const QString &message);
protected:
    virtual void onNewConnection();
    virtual void onClientDisconnected();
    virtual void onConnectionError(QTcpSocket::SocketError error);
    virtual void onClientReadyRead();
    virtual void notificateAll(Socket *sender, const QString &message);
private:
    QList<Socket*> m_clients;
    QHash<Socket*, QByteArray> m_received;
};

#endif // SERVER_H
