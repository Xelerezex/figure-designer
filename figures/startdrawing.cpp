#include "startdrawing.h"

#include <QGraphicsSceneMouseEvent>

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

StartDrawing::StartDrawing(QGraphicsSceneMouseEvent* mouseEvent)
	: FigureAction{}
	, m_mouseEvent{mouseEvent}
{
}

StartDrawing::~StartDrawing()
{
	m_mouseEvent = nullptr;
}

void StartDrawing::act(Circle* circle)
{
	circle->startCreating();
	circle->setCenter(m_mouseEvent->scenePos());
	circle->setDestination(m_mouseEvent->scenePos() + QPointF{0.1, 0.1});
}

void StartDrawing::act(Square* square)
{
	square->startCreating();
	square->setCenter(m_mouseEvent->scenePos());
	square->setDestination(m_mouseEvent->scenePos() + QPointF{0.1, 0.1});
}

void StartDrawing::act(Triangle* triangle)
{
	triangle->startCreating();
	// Обратный порядок, что бы правильно задавался статус отрисовки
	// треугольника:
	triangle->setFirst(m_mouseEvent->scenePos());
	triangle->setSecond(m_mouseEvent->scenePos() + QPointF{0.1, 0.1});

	triangle->setStatus(Triangle::DrawingStatus::FirstPointDrawn);
	triangle->startDrawingLine();
}

void StartDrawing::act(Rectangle* rectangle)
{
	rectangle->startCreating();
	rectangle->setCenter(m_mouseEvent->scenePos());
	rectangle->setDestination(m_mouseEvent->scenePos() + QPointF{0.1, 0.1});
}
