#include "point.h"

Point::Point(double x, double y)
    : m_positionX{x}
    , m_positionY{y}
{
}

double Point::x() const
{
    return m_positionX;
}

double Point::y() const
{
    return m_positionY;
}

void Point::setX(double x)
{
    m_positionX = x;
}

void Point::setY(double y)
{
    m_positionX = y;
}

void Point::setPosition(double x, double y)
{
    m_positionX = x;
    m_positionY = y;
}
