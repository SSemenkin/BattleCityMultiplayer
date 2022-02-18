#include "message.h"

Message::Message(const QByteArray& data) : m_data(data)
{

}

Message::Message(QByteArray &&rhs) noexcept : m_data(rhs)
{

}

Message::Type Message::type() const
{
    return m_type;
}
