#include "GameObject.h"

GameObject::GameObject(const QPixmap &pixmap, QGraphicsItem *parentItem, QObject *parent):
    QObject(parent), QGraphicsPixmapItem(pixmap, parentItem)
{
    setRequireToDestroy(false);
    setBorderPoint(QPointF(0, 0));
    setDestructible(false);
    setBulletCanMoveThroughObject(false);
    setActorCanMoveThroughObject(false);
    setLivesLeft(1);
    setPickable(false);
    setPicked(false);
    setGameObjectName("GameObject");
}

void GameObject::setProperty(const GameObject::Property &key, const QVariant &value)
{
    m_properties.insert(key, value);
}

const QVariant& GameObject::getProperty(const GameObject::Property &key) const
{
    return *m_properties.find(key);
}

bool GameObject::isDestructible() const
{
    return getProperty(GameObject::Property::Destructible).toBool();
}

void GameObject::setDestructible(bool state)
{
    setProperty(GameObject::Property::Destructible, state);
}

bool GameObject::isBulletCanMoveThroughObject() const
{
    return getProperty(GameObject::Property::CanBulletMovesThroughObject).toBool();
}

void GameObject::setBulletCanMoveThroughObject(bool state)
{
    setProperty(GameObject::Property::CanBulletMovesThroughObject, state);
}

bool GameObject::isActorCanMoveThroughObject() const
{
    return getProperty(GameObject::Property::CanActorMovesThroughObject).toBool();
}

void GameObject::setActorCanMoveThroughObject(bool state)
{
    setProperty(GameObject::Property::CanActorMovesThroughObject, state);
}

uint GameObject::livesLeft() const
{
    return getProperty(GameObject::Property::LivesLeft).toUInt();
}

void GameObject::setLivesLeft(uint livesLeft)
{
    setProperty(GameObject::Property::LivesLeft, livesLeft);
    emit livesLeftChanged(livesLeft);
    if (livesLeft == 0) {
        setRequireToDestroy();
    }
}

bool GameObject::isRequireToDestroy() const
{
    return getProperty(GameObject::Property::RequireToDestroy).toBool();
}

void GameObject::setRequireToDestroy(bool state)
{
    setProperty(GameObject::Property::RequireToDestroy, state);
}

QString GameObject::GameObjectName() const
{
    return getProperty(GameObject::Property::GameObjectName).toString();
}

void GameObject::setGameObjectName(const QString &name)
{
    setProperty(GameObject::Property::GameObjectName, name);
}

void GameObject::takeDamage()
{
    int lives = livesLeft();
    lives--;
    setLivesLeft(lives);
}

void GameObject::setBorderPoint(const QPointF &point)
{
    m_border = point;
}

const QPointF &GameObject::borderPoint() const
{
    return m_border;
}

bool GameObject::isPicked() const
{
    return getProperty(GameObject::Property::Picked).toBool();
}

void GameObject::setPicked(bool state)
{
    setProperty(GameObject::Property::Picked, state);
}

bool GameObject::isPickable() const
{
    return getProperty(GameObject::Property::Pickable).toBool();
}

void GameObject::setPickable(bool state)
{
    setProperty(GameObject::Property::Pickable, state);
}

void GameObject::advance(int phase)
{
    if (phase) {
        if (isRequireToDestroy()) {
            delete this;
        }
    }
}

