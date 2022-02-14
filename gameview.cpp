#include "gameview.h"
#include "network/server.h"
#include "menuscene.h"

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent),
      m_menuScene(new MenuScene)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    setScene(&*m_menuScene);
}

GameView::~GameView()
{
}

