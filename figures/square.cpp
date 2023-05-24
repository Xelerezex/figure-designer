#include "square.h"

Square::Square(double side)
    : Figures{Point{0, 0}}
    , m_side{side}
{
    calculateStartCoordinate(side);
}

double Square::side() const
{
    return m_side;
}

Point Square::point(SquarePoint point) const
{
    Point result;
    switch (point)
    {
        case (SquarePoint::First):
        {
            result = m_first;
            break;
        }
        case (SquarePoint::Second):
        {
            result = m_second;
            break;
        }
        case (SquarePoint::Third):
        {
            result = m_third;
            break;
        }
        case (SquarePoint::Fourth):
        {
            result = m_fourth;
            break;
        }
    }
    return result;
}

void Square::calculateStartCoordinate(double side)
{
    double halfSide = side / 2;

    m_first = Point{
        position().x() - halfSide,
        position().y() + halfSide,
    };
    m_second = Point{
        position().x() + halfSide,
        position().y() + halfSide,
    };
    m_third = Point{
        position().x() + halfSide,
        position().y() - halfSide,
    };
    m_fourth = Point{
        position().x() - halfSide,
        position().y() - halfSide,
    };
}
