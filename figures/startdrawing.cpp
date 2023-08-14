#include "startdrawing.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

StartDrawing::StartDrawing(const QPointF& itemCoord, const QPointF& sceneCoord)
	: FigureAction{}
	, m_itemCoord{itemCoord}
	, m_sceneCoord{sceneCoord}
	, m_defaultShift{0.1, 0.1}
{
}

StartDrawing::~StartDrawing()
{
}

void StartDrawing::act(Circle* circle)
{
	circle->startCreating();
	circle->setCenter(m_itemCoord);
	circle->setDestination(m_itemCoord + m_defaultShift);
	circle->setPos(m_sceneCoord - m_itemCoord);
}

void StartDrawing::act(Square* square)
{
	square->startCreating();
	square->setCenter(m_itemCoord);
	square->setDestination(m_itemCoord + m_defaultShift);
	square->setPos(m_sceneCoord - m_itemCoord);
}

void StartDrawing::act(Triangle* triangle)
{
	triangle->startCreating();
	// Обратный порядок, что бы правильно задавался статус отрисовки
	// треугольника:
	triangle->setFirst(m_itemCoord);
	triangle->setSecond(m_itemCoord + m_defaultShift);
	triangle->setPos(m_sceneCoord - m_itemCoord);

	triangle->setStatus(Triangle::DrawingStatus::FirstPointDrawn);
	triangle->startDrawingLine();
}

void StartDrawing::act(Rectangle* rectangle)
{
	rectangle->startCreating();
	rectangle->setCenter(m_itemCoord);
	rectangle->setDestination(m_itemCoord + m_defaultShift);
	rectangle->setPos(m_sceneCoord - m_itemCoord);
}
