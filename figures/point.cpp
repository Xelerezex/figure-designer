#include "point.h"

Point::Point(int x, int y)
    : m_positionX{x}
    , m_positionY{y}
{
}

int Point::x() const
{
    return m_positionX;
}

int Point::y() const
{
    return m_positionY;
}

void Point::setX(int x)
{
    m_positionX = x;
}

void Point::setY(int y)
{
    m_positionX = y;
}

void Point::setPosition(int x, int y)
{
    m_positionX = x;
    m_positionY = y;
}
