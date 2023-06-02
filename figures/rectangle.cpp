#include "rectangle.h"

Rectangle::Rectangle(double width, double height)
    : Figures{Point{0, 0}}
    , m_width{width}
    , m_height{height}

{
    calculateStartCoordinate(width, height);
}

double Rectangle::height() const
{
    return m_height;
}

double Rectangle::width() const
{
    return m_width;
}

Point Rectangle::point(RectanglePoint point) const
{
    Point result;
    switch (point)
    {
        case (RectanglePoint::First):
        {
            result = m_first;
            break;
        }
        case (RectanglePoint::Second):
        {
            result = m_second;
            break;
        }
        case (RectanglePoint::Third):
        {
            result = m_third;
            break;
        }
        case (RectanglePoint::Fourth):
        {
            result = m_fourth;
            break;
        }
    }
    return result;
}

void Rectangle::calculateStartCoordinate(double width, double height)
{
    double halfWidth  = width / 2;
    double halfHeight = height / 2;

    m_first = Point{
        position().x() - halfWidth,
        position().y() + halfHeight,
    };
    m_second = Point{
        position().x() + halfWidth,
        position().y() + halfHeight,
    };
    m_third = Point{
        position().x() + halfWidth,
        position().y() - halfHeight,
    };
    m_fourth = Point{
        position().x() - halfWidth,
        position().y() - halfHeight,
    };
}
