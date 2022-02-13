#include "gameview.h"

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
{

    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

}

GameView::~GameView()
{
}

