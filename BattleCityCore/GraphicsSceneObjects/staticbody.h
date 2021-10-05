#ifndef STATICBODY_H
#define STATICBODY_H

#include "GraphicsSceneObjects/GameObject.h"

class BATTLECITYCORE_EXPORT StaticBody : public GameObject
{
    Q_OBJECT
public:
    enum class Type : int8_t {
        Brick = 0,
        Bush,
        Concrete,
        Water
    };
    explicit StaticBody(Type type, int width);
private:
    void init();
    void changePixmap();
    void createTimer();
private:
    int m_width;
    Type m_type;
    bool m_requireSwapPixmap {true};
};

#endif // STATICBODY_H
