#include "gamescene.h"

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent),
    m_gameTimer(new QTimer(this)),
    m_bonusTimer(new QTimer(this)),
    m_enemySpawnTimer(new QTimer(this)),
    m_borderTimer(new QTimer(this)),
    m_borderBlinkTimer(new QTimer(this))
{
    calcRects();
    setSceneRect(qApp->primaryScreen()->availableGeometry());
    setBackgroundBrush(QColor(126, 126, 126));
}

bool GameScene::loadLevel(const Level &level)
{
    bool result = level.isOk();
    if (result) {

        m_enemyCount = level.enemyCount();
        LevelStructure environment = level.levelStructure();

        m_lengthBlock = qMin(gameplayRect().height() / environment.size(),
                             gameplayRect().width() / environment.first().size());
        m_lastHeight = m_lengthBlock * environment.size();

        for (int i = 0; i < environment.size(); ++i) {
            for (int j = 0; j < environment.at(i).size(); ++j) {
                if (environment.at(i).at(j).toLatin1() != 32) {
                    StaticBody *body = new StaticBody(static_cast<StaticBody::Type>(environment.at(i).at(j).toLatin1() - '0'), m_lengthBlock);
                    addItem(body);
                    body->setPos(j * m_lengthBlock,
                                 i * m_lengthBlock);
                }
                if (i == environment.size() - 1 && j == environment.at(i).size() - 1) {
                    m_gameplayRect = QRectF(0, 0, j * m_lengthBlock + m_lengthBlock, i * m_lengthBlock + m_lengthBlock);
                }
            }
        }

        initPlayer(level.playerPos());
        initBase(level.basePos());
        initInterface();


        QObject::connect(m_gameTimer,        &QTimer::timeout, this, &GameScene::advance);
        QObject::connect(m_enemySpawnTimer,  &QTimer::timeout, this, &GameScene::spawnEnemy);
        QObject::connect(m_bonusTimer,       &QTimer::timeout, this, &GameScene::spawnBonus);


        m_gameTimer->start(FPS_DELTA);
        m_enemySpawnTimer->start(ENEMY_RESPAWN_DELTA);
        m_bonusTimer->start(BONUS_RESPAWN_DELTA);

    }
    return result;
}

int GameScene::levelId() const
{
    return m_levelId;
}

QRectF GameScene::gameplayRect() const
{
    return m_gameplayRect;
}

QRectF GameScene::interfaceRect() const
{
    return m_interfaceRect;
}

void GameScene::gameOver()
{
    m_bonusTimer->stop();
    m_enemySpawnTimer->stop();
}

void GameScene::gameWin()
{
    m_bonusTimer->stop();
    m_enemySpawnTimer->stop();
    emit toMenu();
}

void GameScene::calcRects()
{
    QRectF avaliableGeometry = qApp->primaryScreen()->availableGeometry();
    m_gameplayRect = avaliableGeometry.adjusted(0, 0, -avaliableGeometry.width()/4, 0);
    m_interfaceRect = avaliableGeometry.adjusted(3 * avaliableGeometry.width()/4, 0, 0, 0);
}

void GameScene::initPlayer(const QPointF &pos)
{
}

void GameScene::initBase(const QPointF &pos)
{

}

void GameScene::spawnEnemy()
{

}

void GameScene::spawnBonus()
{

}

void GameScene::spawnBorder()
{

}

void GameScene::destroyAllEnemies()
{

}

void GameScene::removeBorder()
{
    while(!m_border.isEmpty()) {
        m_border.first()->setRequireToDestroy();
        m_border.removeFirst();
    }

    while(!m_hides.isEmpty()) {
        m_hides.first()->show();
        m_hides.removeFirst();
    }

    QObject::disconnect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::borderBlink);
    QObject::connect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::startBorderBlinking);
}

void GameScene::startBorderBlinking()
{
    m_borderBlinkTimer->stop();
    QObject::disconnect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::startBorderBlinking);
    QObject::connect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::borderBlink);
    m_borderBlinkTimer->start(SWAP_PIXMAPS_DELTA);
}

void GameScene::borderBlink()
{
    for (int i = 0; i < m_border.size(); ++i) {
        m_border.at(i)->isVisible() ? m_border.at(i)->hide() : m_border.at(i)->show();
    }
}

void GameScene::resetBorderTimers()
{
    if(m_borderTimer->isActive()) {
        m_borderTimer->stop();
        m_borderBlinkTimer->stop();

        QObject::disconnect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::borderBlink);
        QObject::disconnect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::startBorderBlinking);


        for (int i = 0; i < m_border.size(); ++i) {
            m_border.at(i)->show();
        }
    }
    QObject::connect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::startBorderBlinking);
    QObject::connect(m_borderTimer,      &QTimer::timeout, this, &GameScene::removeBorder);

    m_borderTimer->start(BONUS_DURATION);
    m_borderBlinkTimer->start(BONUS_DURATION - 2000);
}

void GameScene::initInterface()
{

}

void GameScene::spawnExplosionAt(GameObject *gameObject)
{

}

void GameScene::enemyDestroyed()
{
    m_score+=100;
    if (m_score  == m_enemyCount * 100) {
        gameWin();
    }
    rebuildScore();
    if (!m_enemiesLives.isEmpty()) {
        m_enemiesLives.last()->setRequireToDestroy();
        m_enemiesLives.pop_back();
    }
}

void GameScene::rebuildScore()
{
}

void GameScene::showScore()
{
    for (int i = 0 ; i < m_scoreItems.size(); ++i) {
        addItem(m_scoreItems.at(i));
        m_scoreItems.at(i)->setPos(m_scoreX + i * m_lengthBlock, m_scoreY);
    }
}

void GameScene::hideGameObjectAndCreateConcrete(const QPointF &nearPos)
{

}

void GameScene::playerPickedBonus(int bonus)
{

}

QPointF GameScene::getAvaliablePoint() const
{
    QPointF p;

    for (;;) {
        p.setX(rand() % static_cast<int>(interfaceRect().width() - m_lengthBlock));
        p.setY(rand() % static_cast<int>(m_lastHeight - m_lengthBlock));

        if (isCellAvaliable(p)) {
            return p;
        }
    }
}

bool GameScene::isCellAvaliable(const QPointF &point) const
{
    QTransform transform;
    QGraphicsItem *topLeft = itemAt(point, transform);
    QGraphicsItem *topRight = itemAt(QPointF(point.x() + m_lengthBlock, point.y()), transform);
    QGraphicsItem *leftBottom = itemAt(QPointF(point.x(), point.y() + m_lengthBlock), transform);
    QGraphicsItem *rightBottom = itemAt(QPointF(point.x() + m_lengthBlock, point.y() + m_lengthBlock), transform);
    QGraphicsItem *center = itemAt(QPointF(point.x() + m_lengthBlock/2, point.y() + m_lengthBlock/2), transform);

    bool iAtPos = true;
    for (int i = 0; i < m_border.size(); ++i) {
        if (itemAt(point, transform) == m_border.at(i)) {
            iAtPos = false;
            break;
        }
    }
    return !topLeft && !topRight && !leftBottom && !rightBottom && !center && iAtPos;
}
