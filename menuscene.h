#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "fullscreenscene.h"

class MenuScene : public FullScreenScene
{
    Q_OBJECT
public:
    explicit MenuScene(QObject *parent = nullptr);
};

#endif // MENUSCENE_H
