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
	, m_currentStatus{NotDrawn}
	, m_drawingLine{false}
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

bool Triangle::isFirstDrawn() const
{
	return m_currentStatus == FirstPointDrawn;
}

void Triangle::setSecond(QPointF newSecond)
{
	m_second = newSecond;
}

bool Triangle::isSecondDrawn() const
{
	return m_currentStatus == SecondPointDrawn;
}

void Triangle::setThird(QPointF newThird)
{
	m_third = newThird;
}

bool Triangle::isThirdDrawn() const
{
	return m_currentStatus == ThirdPointDrawn;
}

void Triangle::startDrawingLine()
{
	m_drawingLine = true;
}

void Triangle::stopDrawingLine()
{
	m_drawingLine = false;
}

bool Triangle::isLineDrawing() const
{
	return m_drawingLine;
}

QRectF Triangle::boundingRect() const
{
	return countFigure().normalized();
}

void Triangle::paint(QPainter*						 painter,
					 const QStyleOptionGraphicsItem* option,
					 QWidget*						 widget)
{
	if (m_currentStatus == NotDrawn)
	{
		return;
	}

	const qreal penWidth{3};
	const int	color{8932827};

	//  Класс для отрисовки границы фигуры
	QPen drawingPen
		= {Qt::black, penWidth, Qt::DashLine, Qt::FlatCap, Qt::MiterJoin};

	QPainterPath pathTitle;
	pathTitle.setFillRule(Qt::OddEvenFill);

	if (isLineDrawing() && isFirstDrawn())
	{
		pathTitle.moveTo(m_first);
		pathTitle.lineTo(m_second);
	}
	else if (isLineDrawing() && isSecondDrawn())
	{
		pathTitle.moveTo(m_first);
		pathTitle.lineTo(m_second);
		pathTitle.lineTo(m_third);
	}
	else if (isThirdDrawn())
	{
		if (!isSelected())
		{
			drawingPen = {
				Qt::black, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin};
		}
		pathTitle.addPolygon(countPolygon());
		painter->setBrush(QBrush(color));
	}

	painter->setPen(drawingPen);
	painter->drawPath(pathTitle);
}

QPainterPath Triangle::shape() const
{
	QPainterPath path;
	path.addPolygon(countPolygon());
	return path;
}

QPolygonF Triangle::countPolygon() const
{
	QPolygonF polygon;
	polygon << m_first << m_second << m_third << m_first;
	return polygon;
}

QRectF Triangle::countFigure() const
{
	return countPolygon().boundingRect().normalized();
}

void Triangle::setStatus(DrawingStatus newStatus)
{
	m_currentStatus = newStatus;
}
