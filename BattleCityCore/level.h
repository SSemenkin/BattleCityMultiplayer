#ifndef LEVEL_H
#define LEVEL_H
#include "BattleCityCore_global.h"

#include <QFile>
#include <QPointF>
#include <QDebug>

using LevelStructure = QVector<QString>;

class BATTLECITYCORE_EXPORT Level
{
public:
    Level(const QString &path);
    explicit Level(const QByteArray &rawData);
    [[nodiscard]] int levelId() const;
    [[nodiscard]] int enemyCount() const;
    [[nodiscard]] QPointF playerPos() const;
    [[nodiscard]] QPointF basePos() const;
    [[nodiscard]] bool isOk() const;
    [[nodiscard]] LevelStructure levelStructure() const;
    [[nodiscard]] QByteArray rawLevelStructure() const;

private:
    int m_levelId {-1};
    int m_enemyCount {0};
    QPointF m_invalidPos {-1, -1};
    QPointF m_playerPos;
    QPointF m_basePos;
    LevelStructure m_levelStructure;
    QByteArray m_rawLevelStructure;

private:
    void load(const QString &path);
    void load(const QByteArray &raw);
};

#endif // LEVEL_H
