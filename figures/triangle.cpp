#include "triangle.h"

#include <QPainter>

// DEBUG:
#include <QDebug>

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"

Triangle::Triangle(QGraphicsItem* parent)
	: FigureBase{parent}
	, m_center{0.0, 0.0}
	, m_first{0.0, 0.0}
{
}

Triangle::~Triangle()
{
	// DEBUG:
	qDebug("Triangle deleted");
}

void Triangle::act(StartDrawing&& startDrawing)
{
	startDrawing.act(this);
}

void Triangle::act(ContinueDrawing&& continueDrawing)
{
	continueDrawing.act(this);
}

void Triangle::act(CompleteDrawing&& completeDrawing)
{
	completeDrawing.act(this);
}

QPointF Triangle::center() const
{
	return m_center;
}

void Triangle::setCenter(QPointF newCenter)
{
	m_center = newCenter;
}

void Triangle::setFirst(QPointF newFirst)
{
	m_first = newFirst;
}

void Triangle::setThird(QPointF newThird)
{
	m_third = newThird;
}

void Triangle::setSecond(QPointF newSecond)
{
	m_second = newSecond;
}

QRectF Triangle::boundingRect() const
{
	return countFigure().normalized();
}

void Triangle::paint(QPainter*						 painter,
					 const QStyleOptionGraphicsItem* option,
					 QWidget*						 widget)
{
}

QPainterPath Triangle::shape() const
{
	QPainterPath path;
	path.addPolygon(countFigure());
	return path;
}

QRectF Triangle::countFigure() const
{
	QPolygonF polygon;
	polygon << m_first << m_second << m_third;

	return polygon.boundingRect().normalized();
}
