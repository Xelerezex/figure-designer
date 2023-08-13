#include "completedrawing.h"

#include <QGraphicsSceneMouseEvent>

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

CompleteDrawing::CompleteDrawing(QGraphicsSceneMouseEvent* mouseEvent)
	: FigureAction{}
	, m_mouseEvent{mouseEvent}
{
}

CompleteDrawing::~CompleteDrawing()
{
	m_mouseEvent = nullptr;
}

void CompleteDrawing::act(Circle* circle)
{
	circle->setDestination(m_mouseEvent->scenePos());
	circle->completeCreating();
	circle->update();
}

void CompleteDrawing::act(Square* square)
{
	square->setDestination(m_mouseEvent->scenePos());
	square->completeCreating();
	square->update();
}

void CompleteDrawing::act(Triangle* triangle)
{
	if (triangle->isFirstDrawn())
	{
		triangle->setSecond(m_mouseEvent->scenePos());
		// Третьей точке задается координата, что бы не было разрывов
		triangle->setThird(m_mouseEvent->scenePos());
		triangle->setStatus(Triangle::DrawingStatus::SecondPointDrawn);
		triangle->update();
	}
	else if (triangle->isSecondDrawn())
	{
		triangle->setThird(m_mouseEvent->scenePos());
		triangle->setStatus(Triangle::DrawingStatus::ThirdPointDrawn);
		triangle->stopDrawingLine();
		triangle->completeCreating();
		triangle->update();
	}
}

void CompleteDrawing::act(Rectangle* rectangle)
{
	rectangle->setDestination(m_mouseEvent->scenePos());
	rectangle->completeCreating();
	rectangle->update();
}
