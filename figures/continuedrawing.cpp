#include "continuedrawing.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"
#include "selectionrectangle.h"

ContinueDrawing::ContinueDrawing(const QPointF& itemCoord)
	: m_itemCoord{itemCoord}
{
}

ContinueDrawing::~ContinueDrawing()
{
}

void ContinueDrawing::act(Circle* circle)
{
	circle->setDestination(m_itemCoord);
}

void ContinueDrawing::act(Square* square)
{
	square->setDestination(m_itemCoord);
}

void ContinueDrawing::act(Triangle* triangle)
{
	if (triangle->isFirstDrawn() && triangle->isLineDrawing())
	{
		triangle->setSecond(m_itemCoord);
		triangle->update();
	}
	else if (triangle->isSecondDrawn() && triangle->isLineDrawing())
	{
		triangle->setThird(m_itemCoord);
		triangle->update();
	}
}

void ContinueDrawing::act(Rectangle* rectangle)
{
	rectangle->setDestination(m_itemCoord);
}

void ContinueDrawing::act(SelectionRectangle* selectRect)
{
	selectRect->setDestination(m_itemCoord);
}
