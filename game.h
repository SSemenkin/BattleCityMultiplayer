#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "gameview.h"
#include "network/socket.h"

class Game : public QObject
{
    Q_DISABLE_COPY_MOVE(Game);
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    void requestStartPosition(Socket *client);
    void init();

signals:

private:

    QScopedPointer<GameView> m_gameView;
};

#endif // GAME_H
