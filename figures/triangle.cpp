#include "triangle.h"

#include <stdexcept>

Triangle::Triangle(Point first, Point second, Point third)
    : Figures{Point{0, 0}}
    , m_first{first}
    , m_second{second}
    , m_third{third}
{
    if (!checkExisting(first, second, third))
    {
        throw std::logic_error("Cannot create such triangle");
    }
}

Point Triangle::point(TrianglePoint point) const
{
    Point result;
    switch (point)
    {
        case (TrianglePoint::First):
        {
            result = m_first;
            break;
        }
        case (TrianglePoint::Second):
        {
            result = m_second;
            break;
        }
        case (TrianglePoint::Third):
        {
            result = m_third;
            break;
        }
    }
    return result;
}

bool Triangle::checkExisting(Point first, Point second, Point third)
{
    double firstSide  = distance(first, third);
    double secondSide = distance(third, second);
    double thirdSide  = distance(second, first);

    bool   condOne	 = firstSide + secondSide > thirdSide;
    bool   condTwo	 = firstSide + thirdSide > secondSide;
    bool   condThree = secondSide + thirdSide > firstSide;

    return condOne && condTwo && condThree;
}

double Triangle::distance(Point first, Point second)
{
    double result = std::hypot(second.x() - first.x(), second.y() - first.y());
    return result;
}
