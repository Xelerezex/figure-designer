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
	circle->update();
}

void ContinueDrawing::act(Square* square)
{
	square->setDestination(m_itemCoord);
	square->update();
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
	rectangle->update();
}

void ContinueDrawing::act(SelectionRectangle* selectRect)
{
	// Если на этом этапе метода еще не существует - начинаем его создание
	if (selectRect->isNotExisting())
	{
		selectRect->startCreating();
	}

	selectRect->setDestination(m_itemCoord);
}
