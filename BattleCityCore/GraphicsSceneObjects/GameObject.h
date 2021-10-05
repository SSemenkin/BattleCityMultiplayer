#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#define SWAP_PIXMAPS_DELTA 150
#define BONUS_DURATION 7000
#define ENEMY_SWAP_DIRECTION_DELTA 1000
#define ENEMY_SHOOT_DELTA 1000
#define TANK_SPEED 4
#define BULLET_SPEED 6
#define SCORE_DURATION 2000

#include <QObject>
#include <QGraphicsObject>
#include <QMap>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

class GameObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameObject(const QPixmap &pixmap = QPixmap(),
           QGraphicsItem *parentItem = nullptr,
           QObject *parent = nullptr);

    enum class Property : int8_t {
        Destructible = 0,
        CanBulletMovesThroughObject,
        CanActorMovesThroughObject,
        LivesLeft,
        RequireToDestroy,
        GameObjectName,
        Pickable,
        Picked
    };


    bool isDestructible() const;
    void setDestructible(bool state);

    bool isBulletCanMoveThroughObject() const;
    void setBulletCanMoveThroughObject(bool state);

    bool isActorCanMoveThroughObject() const;
    void setActorCanMoveThroughObject(bool state);

    uint livesLeft() const;
    void setLivesLeft(uint livesLeft);

    bool isRequireToDestroy() const;
    void setRequireToDestroy(bool state = true);

    QString GameObjectName() const;
    void setGameObjectName(const QString &name);

    virtual void takeDamage();

    void setBorderPoint(const QPointF& point);
    const QPointF& borderPoint() const;

    bool isPicked() const;
    void setPicked(bool state = true);

    bool isPickable() const;
    void setPickable(bool state);


signals:
    void picked(int type);
    void livesLeftChanged(int health);

protected:
    virtual void advance(int phase) override;

    void setProperty(const Property &key, const QVariant &value);
    const QVariant& getProperty(const Property &key) const;

private:
    QMap<Property, QVariant> m_properties;
    QPointF m_border;
};

inline QDebug operator<< (QDebug dbg, const GameObject::Property &property)
{
    QString m_property;
    switch (property) {
        case GameObject::Property::CanActorMovesThroughObject:
        {
            m_property = "GameObject::Property::CanActorMovesThroughObject ";
            break;
        }
        case GameObject::Property::CanBulletMovesThroughObject:
        {
            m_property = "GameObject::Property::CanBulletMovesThroughObject ";
            break;
        }
        case GameObject::Property::Destructible:
        {
            m_property = "GameObject::Property::Destructible ";
            break;
        }
        case GameObject::Property::GameObjectName:
        {
            m_property = "GameObject::Property::GameObjectName ";
            break;
        }
        case GameObject::Property::RequireToDestroy:
        {
            m_property = "GameObject::Property::RequireToDestroy";
            break;
        }
        case GameObject::Property::LivesLeft:
        {
            m_property = "GameObject::Property::LivesLeft ";
            break;
        }
        case GameObject::Property::Pickable:
        {
            m_property = "GameObject::Property::Pickable ";
            break;
        }
        case GameObject::Property::Picked:
        {
            m_property = "GameObject::Property::Picked ";
            break;
        }
    }
    dbg.nospace() << qUtf8Printable(m_property);

    return dbg.maybeSpace();
}

#endif // GAMEOBJECT_H
