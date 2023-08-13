#include "completedrawing.h"

// DEBUG:
#include <QDebug>

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
	// DEBUG:
	qDebug("CompleteDrawing deleted");
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
}

void CompleteDrawing::act(Rectangle* rectangle)
{
	rectangle->setDestination(m_mouseEvent->scenePos());
	rectangle->completeCreating();
	rectangle->update();
}
