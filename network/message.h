#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>

class Message
{
public:

    enum class Type {
        Unknown = -1,
        RequestStartPosition,
        RequestChangePosition,
        RequestFire

    };

    explicit Message(const QByteArray &);
    explicit Message(QByteArray &&) noexcept;

    Type type() const;

private:
    QByteArray m_data;
    Type m_type {Type::Unknown};
};

#endif // MESSAGE_H
