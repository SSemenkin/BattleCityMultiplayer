#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include <QObject>

class MaximizedScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MaximizedScene(QObject *parent = nullptr);
    virtual ~MaximizedScene();
};

class MenuScene : public MaximizedScene
{
    Q_OBJECT
public:
    explicit MenuScene(QObject *parent = nullptr);

private:
    QGraphicsPixmapItem *m_logoItem;
};

class GameplayScene : public MaximizedScene
{
    Q_OBJECT
public:
    explicit GameplayScene(QObject *parent = nullptr);
};

#endif // MENUSCENE_H
