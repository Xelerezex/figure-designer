#include "completedrawing.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

CompleteDrawing::CompleteDrawing(const QPointF& itemCoord)
	: FigureAction{}
	, m_itemCoord{itemCoord}
{
}

CompleteDrawing::~CompleteDrawing()
{
}

void CompleteDrawing::act(Circle* circle)
{
	circle->setDestination(m_itemCoord);
	circle->completeCreating();
	circle->update();
}

void CompleteDrawing::act(Square* square)
{
	square->setDestination(m_itemCoord);
	square->completeCreating();
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
		triangle->update();
	}
}

void CompleteDrawing::act(Rectangle* rectangle)
{
	rectangle->setDestination(m_itemCoord);
	rectangle->completeCreating();
	rectangle->update();
}
