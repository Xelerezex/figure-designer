#include "completedrawing.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"
#include "selectionrectangle.h"

CompleteDrawing::CompleteDrawing(const QPointF& itemCoord)
	: m_itemCoord{itemCoord}
{
}

CompleteDrawing::~CompleteDrawing()
{
}

void CompleteDrawing::act(Circle* circle)
{
	circle->setDestination(m_itemCoord);
	circle->completeCreating();
	circle->setSelected(false);
	circle->update();
}

void CompleteDrawing::act(Square* square)
{
	square->setDestination(m_itemCoord);
	square->completeCreating();
	square->setSelected(false);
	square->update();
}

void CompleteDrawing::act(Triangle* triangle)
{
	if (triangle->isFirstDrawn())
	{
		triangle->setSecond(m_itemCoord);
		// Третьей точке так же задается координата, что бы не было разрывов
		// при отрисовке
		triangle->setThird(m_itemCoord);
		triangle->setStatus(Triangle::DrawingStatus::SecondPointDrawn);
		triangle->update();
	}
	else if (triangle->isSecondDrawn())
	{
		triangle->setThird(m_itemCoord);
		triangle->setStatus(Triangle::DrawingStatus::ThirdPointDrawn);
		triangle->stopDrawingLine();
		triangle->completeCreating();
		triangle->setSelected(false);
		triangle->update();
	}
}

void CompleteDrawing::act(Rectangle* rectangle)
{
	rectangle->setDestination(m_itemCoord);
	rectangle->completeCreating();
	rectangle->setSelected(false);
	rectangle->update();
}

void CompleteDrawing::act(SelectionRectangle* selectRect)
{
	selectRect->setDestination(m_itemCoord);
	selectRect->completeCreating();
	selectRect->setSelected(false);
	selectRect->update();
}
