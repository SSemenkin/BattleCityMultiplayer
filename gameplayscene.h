#ifndef GAMEPLAYSCENE_H
#define GAMEPLAYSCENE_H

#include "fullscreenscene.h"

class GameplayScene : public FullScreenScene
{
    Q_OBJECT
public:
    explicit GameplayScene(QObject *parent = nullptr);
};

#endif // GAMEPLAYSCENE_H
