#include "triangle.h"

#include <QPainter>

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"

Triangle::Triangle(QMenu* fileMenu, QGraphicsItem* parent)
	: FigureBase{fileMenu, parent}
	, m_currentStatus{NotDrawn}
	, m_drawingLine{false}
	, m_first{0.0, 0.0}
{
}

Triangle::~Triangle()
{
}

int Triangle::type() const
{
	return FigureBase::Triangle;
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

const QPointF& Triangle::first() const
{
	return m_first;
}

void Triangle::setFirst(const QPointF& newFirst)
{
	m_first = newFirst;
}

bool Triangle::isFirstDrawn() const
{
	return m_currentStatus == FirstPointDrawn;
}

const QPointF& Triangle::second() const
{
	return m_second;
}

void Triangle::setSecond(const QPointF& newSecond)
{
	m_second = newSecond;
}

bool Triangle::isSecondDrawn() const
{
	return m_currentStatus == SecondPointDrawn;
}

const QPointF& Triangle::third() const
{
	return m_third;
}

void Triangle::setThird(const QPointF& newThird)
{
	m_third = newThird;
	// Устанавливаем центр фигуры, после того, как узнали координаты третьей
	// точки
	setCenter(countCenter());
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
	Q_UNUSED(option);
	Q_UNUSED(widget);

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

QPointF Triangle::countCenter() const
{
	QPointF center{(m_first.x() + m_second.x() + m_third.x()) / 3,
				   (m_first.y() + m_second.y() + m_third.y()) / 3};

	return center;
}
