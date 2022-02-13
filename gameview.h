#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <qamqp/qamqpclient.h>

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView(QWidget *parent = nullptr);
    ~GameView();

};
#endif // GAMEVIEW_H
