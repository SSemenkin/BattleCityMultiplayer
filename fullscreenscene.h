#ifndef FULLSCREENSCENE_H
#define FULLSCREENSCENE_H

#include <QGraphicsScene>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QObject *parent = nullptr) : QGraphicsScene(parent) {}
signals:
    void quit();
};

class FullScreenScene : public CustomScene
{
    Q_OBJECT
public:
    explicit FullScreenScene(QObject *parent = nullptr);
};

#endif // FULLSCREENSCENE_H
