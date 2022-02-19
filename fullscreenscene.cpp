#include "fullscreenscene.h"
#include <QApplication>
#include <QScreen>

FullScreenScene::FullScreenScene(QObject *parent) : QGraphicsScene(parent)
{
    setSceneRect(static_cast<QApplication*>(QApplication::instance())->primaryScreen()->geometry());
}
