#include "client.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    m_socket(new QTcpSocket(this)),
    m_layout(this),
    m_lineEdit(new QLineEdit(this)),
    m_pushButton(new QPushButton("Connect to Server", this))
{
    QObject::connect(m_pushButton, &QPushButton::clicked, this, &Client::connectToServer);
    QObject::connect(m_socket, &QTcpSocket::readyRead, this, &Client::getServerReply);

    m_layout.addWidget(m_lineEdit);
    m_layout.addWidget(m_pushButton);
    gameObject = new GameObject();
}

Client::~Client()
{
    gameObject->setRequireToDestroy();
}

void Client::connectToServer()
{
    m_socket->connectToHost(m_lineEdit->text(), 12345);
}

void Client::getServerReply()
{
    QByteArray raw =  m_socket->readAll();
    QString reply = raw;

}
