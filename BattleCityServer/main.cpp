#include <QCoreApplication>
#include <iostream>
#include "gameserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GameServer gameServer;

    QString hostname;
    int port;
    std::string s;
    std::cout << "Enter server hostname:";
    std::cin >> s;
    std::cout << "Enter server port:";
    std::cin >> port;

    hostname = QString::fromStdString(s);


    if (gameServer.listen(QHostAddress(hostname), port)) {
        qDebug() << QString("Server started on adress: %1 / port: %2.").arg(hostname).arg(port);
    } else {
        qDebug() << QString("Cannot start server at adress: %1 / port: %2.").arg(hostname).arg(port);
    }


    return a.exec();
}
