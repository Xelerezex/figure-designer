#include "continuedrawing.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

ContinueDrawing::ContinueDrawing(QPointF coordinate)
	: FigureAction{}
	, m_coordinate{coordinate}
{
}

ContinueDrawing::~ContinueDrawing()
{
}

void ContinueDrawing::act(Circle* circle)
{
	circle->setDestination(m_coordinate);
}

void ContinueDrawing::act(Square* square)
{
	square->setDestination(m_coordinate);
}

void ContinueDrawing::act(Triangle* triangle)
{
	if (triangle->isFirstDrawn() && triangle->isLineDrawing())
	{
		triangle->setSecond(m_coordinate);
		triangle->update();
	}
	else if (triangle->isSecondDrawn() && triangle->isLineDrawing())
	{
		triangle->setThird(m_coordinate);
		triangle->update();
	}
}

void ContinueDrawing::act(Rectangle* rectangle)
{
	rectangle->setDestination(m_coordinate);
}
