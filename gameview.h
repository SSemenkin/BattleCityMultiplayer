#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>


class Server;
class MenuScene;
class GameplayScene;

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView(QWidget *parent = nullptr);
    ~GameView();

    QSharedPointer<MenuScene> menuScene() const;
    QSharedPointer<GameplayScene> gameplayScene() const;

private:
    QSharedPointer<MenuScene>     m_menuScene;
    QSharedPointer<GameplayScene> m_gameplayScene;
};
#endif // GAMEVIEW_H
