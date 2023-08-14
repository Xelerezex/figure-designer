#include "startdrawing.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

StartDrawing::StartDrawing(QPointF coordinate)
	: FigureAction{}
	, m_coordinate{coordinate}
{
}

StartDrawing::~StartDrawing()
{
}

void StartDrawing::act(Circle* circle)
{
	circle->startCreating();
	circle->setCenter(m_coordinate);
	circle->setDestination(m_coordinate + QPointF{0.1, 0.1});
}

void StartDrawing::act(Square* square)
{
	square->startCreating();
	square->setCenter(m_coordinate);
	square->setDestination(m_coordinate + QPointF{0.1, 0.1});
}

void StartDrawing::act(Triangle* triangle)
{
	triangle->startCreating();
	// Обратный порядок, что бы правильно задавался статус отрисовки
	// треугольника:
	triangle->setFirst(m_coordinate);
	triangle->setSecond(m_coordinate + QPointF{0.1, 0.1});

	triangle->setStatus(Triangle::DrawingStatus::FirstPointDrawn);
	triangle->startDrawingLine();
}

void StartDrawing::act(Rectangle* rectangle)
{
	rectangle->startCreating();
	rectangle->setCenter(m_coordinate);
	rectangle->setDestination(m_coordinate + QPointF{0.1, 0.1});
}
