#include "figures.h"

Figures::Figures(Point p)
    : m_position{p}
{
}

Figures::~Figures()
{
}

Point Figures::position() const
{
    return m_position;
}
