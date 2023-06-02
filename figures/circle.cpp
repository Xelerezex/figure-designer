#include "circle.h"

Circle::Circle(double radPoint)
    : Figures{Point{0, 0}}
    , m_radius{radPoint}

{
}

double Circle::radius() const
{
    return m_radius;
}
