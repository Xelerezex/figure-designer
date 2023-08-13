#include "continuedrawing.h"

#include <QGraphicsSceneMouseEvent>

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

ContinueDrawing::ContinueDrawing(QGraphicsSceneMouseEvent* mouseEvent)
	: FigureAction{}
	, m_mouseEvent{mouseEvent}
{
}

ContinueDrawing::~ContinueDrawing()
{
	m_mouseEvent = nullptr;
}

void ContinueDrawing::act(Circle* circle)
{
	circle->setDestination(m_mouseEvent->scenePos());
}

void ContinueDrawing::act(Square* square)
{
	square->setDestination(m_mouseEvent->scenePos());
}

void ContinueDrawing::act(Triangle* triangle)
{
	if (triangle->isFirstDrawn() && triangle->isLineDrawing())
	{
		triangle->setSecond(m_mouseEvent->scenePos());
		triangle->update();
	}
	else if (triangle->isSecondDrawn() && triangle->isLineDrawing())
	{
		triangle->setThird(m_mouseEvent->scenePos());
		triangle->update();
	}
}

void ContinueDrawing::act(Rectangle* rectangle)
{
	rectangle->setDestination(m_mouseEvent->scenePos());
}
