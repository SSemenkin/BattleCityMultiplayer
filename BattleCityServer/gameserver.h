#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>

class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = nullptr);

signals:

};

#endif // GAMESERVER_H
