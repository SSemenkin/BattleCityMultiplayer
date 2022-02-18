#include "menuscene.h"
#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QScreen>
#include <QDebug>

MenuScene::MenuScene(QObject *parent) : MaximizedScene(parent),
    m_logoItem(new QGraphicsPixmapItem(QPixmap(":/images/logo.png")))
{
    setBackgroundBrush(QColor(126, 126, 126));

    addItem(m_logoItem);
    m_logoItem->setPixmap(m_logoItem->pixmap().scaled(m_logoItem->pixmap().width()/2, m_logoItem->pixmap().height() / 2 ));
    m_logoItem->setPos(width() / 2 - m_logoItem->pixmap().width()/ 2,
                       height() / 2 - m_logoItem->pixmap().height() );
}

MaximizedScene::MaximizedScene(QObject *parent) : QGraphicsScene(parent)
{
    setSceneRect(qApp->primaryScreen()->geometry());
}

MaximizedScene::~MaximizedScene()
{
    qDebug() << Q_FUNC_INFO;
}
