#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr id) override;
    void clientDisconnected();
    void newMessageFromClient();
private:
    QList<QTcpSocket *> m_clients;
    QMap<QTcpSocket*, QString> m_answers;

    template<typename T>
    void validInput(T& value) {
        std::cin >> value;
        if (std::cin.fail()) {
            qDebug() << "Your input is not valid.";
            exit(-1);
        }
    }
};

#endif // SERVER_H
