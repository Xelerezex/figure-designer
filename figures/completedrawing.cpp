#include "completedrawing.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

CompleteDrawing::CompleteDrawing(QPointF coordinate)
	: FigureAction{}
	, m_coordinate{coordinate}
{
}

CompleteDrawing::~CompleteDrawing()
{
}

void CompleteDrawing::act(Circle* circle)
{
	circle->setDestination(m_coordinate);
	circle->completeCreating();
	circle->update();
}

void CompleteDrawing::act(Square* square)
{
	square->setDestination(m_coordinate);
	square->completeCreating();
	square->update();
}

void CompleteDrawing::act(Triangle* triangle)
{
	if (triangle->isFirstDrawn())
	{
		triangle->setSecond(m_coordinate);
		// Третьей точке так же задается координата, что бы не было разрывов
		// при отрисовке
		triangle->setThird(m_coordinate);
		triangle->setStatus(Triangle::DrawingStatus::SecondPointDrawn);
		triangle->update();
	}
	else if (triangle->isSecondDrawn())
	{
		triangle->setThird(m_coordinate);
		triangle->setStatus(Triangle::DrawingStatus::ThirdPointDrawn);
		triangle->stopDrawingLine();
		triangle->completeCreating();
		triangle->update();
	}
}

void CompleteDrawing::act(Rectangle* rectangle)
{
	rectangle->setDestination(m_coordinate);
	rectangle->completeCreating();
	rectangle->update();
}
