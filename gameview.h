#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>


class Server;
class MenuScene;

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView(QWidget *parent = nullptr);
    ~GameView();
private:
    Server *m_server;
    QScopedPointer<MenuScene> m_menuScene;
};
#endif // GAMEVIEW_H
