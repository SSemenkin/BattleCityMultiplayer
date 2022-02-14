#ifndef SOCKET_H
#define SOCKET_H

#define FINISH_TOKEN ';'

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>



class Socket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);

signals:

};

#endif // SOCKET_H
