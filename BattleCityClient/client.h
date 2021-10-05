#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>

#include "GraphicsSceneObjects/GameObject.h"


class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();
    enum class ClientEventType {
        Move,
        Fire
    };
signals:

private:
    QTcpSocket *m_socket;
    QGridLayout m_layout;
    QLineEdit *m_lineEdit;
    QPushButton *m_pushButton;

private:
    void connectToServer();
    void getServerReply();

    GameObject *gameObject;
};

#endif // CLIENT_H
