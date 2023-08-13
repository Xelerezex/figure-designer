#include "continuedrawing.h"

// DEBUG:
#include <QDebug>

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
	// DEBUG:
	qDebug("ContinueDrawing deleted");
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
}

void ContinueDrawing::act(Rectangle* rectangle)
{
	rectangle->setDestination(m_mouseEvent->scenePos());
}
