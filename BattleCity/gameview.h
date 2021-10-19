#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QTcpSocket>

class GameView : public QWidget
{
    Q_OBJECT

public:
    GameView(QWidget *parent = nullptr);
    ~GameView();

private:
    QTcpSocket *m_socket;
};
#endif // GAMEVIEW_H
