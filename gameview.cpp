#include "gameview.h"
#include "menuscene.h"
#include "gameplayscene.h"
#include <QDebug>

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent),
      m_menuScene(new MenuScene),
      m_gameplayScene(new GameplayScene)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setScene(m_menuScene.data());
}

GameView::~GameView()
{
    qDebug() << Q_FUNC_INFO;
}

QSharedPointer<MenuScene> GameView::menuScene() const
{
    return m_menuScene;
}

QSharedPointer<GameplayScene> GameView::gameplayScene() const
{
    return m_gameplayScene;
}

