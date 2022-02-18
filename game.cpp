#include "game.h"

void Game::requestStartPosition(Socket *client)
{

}

void Game::init()
{
    m_gameView.reset(new GameView);
    m_gameView->show();
}

Game::Game(QObject *parent) : QObject(parent)
{

}
