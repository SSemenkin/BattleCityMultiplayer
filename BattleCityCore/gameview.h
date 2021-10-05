#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QGraphicsView>

#include "level.h"
#include "GraphicsScenes/gamescene.h"
#include "GraphicsScenes/menuscene.h"


class BATTLECITYCORE_EXPORT GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView();
    GameView(const GameView& rhs) = delete;
    GameView& operator=(const GameView& rhs) = delete;

    void startGameAtLevel(int levelId);
    void toMenu();

private:

    QScopedPointer<GameScene> m_gameScene;
    QScopedPointer<MenuScene> m_menuScene;

    QVector<Level> m_levelVector;
};

#endif // GAMEVIEW_H
