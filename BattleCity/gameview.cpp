#include "gameview.h"

GameView::GameView(QWidget *parent)
    : QWidget(parent),
      m_socket(new QTcpSocket(this))
{
}

GameView::~GameView()
{
}

