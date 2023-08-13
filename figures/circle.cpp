#include "circle.h"

#include <QPainter>

// DEBUG:
#include <QDebug>

Circle::Circle(QGraphicsItem* parent)
	: FigureBase{parent}
	, m_center{0.0, 0.0}
	, m_destination{0.0, 0.0}
{
}

Circle::~Circle()
{
	// DEBUG:
	qDebug("Circle deleted");
}

QPointF Circle::center() const
{
	return m_center;
}

void Circle::setCenter(QPointF newCenter)
{
	m_center = newCenter;
}

QPointF Circle::destination() const
{
	return m_destination;
}

void Circle::setDestination(QPointF newDestination)
{
	m_destination = newDestination;
}

QRectF Circle::boundingRect() const
{
	return countFigure().normalized();
}

void Circle::paint(QPainter*					   painter,
				   const QStyleOptionGraphicsItem* option,
				   QWidget*						   widget)
{
	const qreal penWidth{3};
	const int	color{16752774};

	// Класс для отрисовки границы фигуры
	QPen drawingPen;

	if (!isFullyCreated())
	{
		drawingPen
			= {Qt::black, penWidth, Qt::DashLine, Qt::FlatCap, Qt::MiterJoin};
	}
	else if (isSelected() && isFullyCreated())
	{
		drawingPen
			= {Qt::black, penWidth, Qt::DashLine, Qt::FlatCap, Qt::MiterJoin};
		painter->setBrush(QBrush(color));
	}
	if (!isSelected() && isFullyCreated())
	{
		drawingPen
			= {Qt::black, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin};
		painter->setBrush(QBrush(color));
	}

	QPainterPath pathTitle;
	pathTitle.setFillRule(Qt::OddEvenFill);

	QRectF frameRect = boundingRect();
	frameRect.setWidth(boundingRect().width() - penWidth);
	frameRect.setHeight(boundingRect().height() - penWidth);
	pathTitle.addEllipse(frameRect);

	painter->setPen(drawingPen);
	painter->drawPath(pathTitle.simplified());
}

QPainterPath Circle::shape() const
{
	QPainterPath path;
	path.addEllipse(boundingRect());
	return path;
}

QRectF Circle::countFigure() const
{
	// Линия между центром и второй точкой фигуры
	QLineF line{m_center, m_destination};

	// Координаты точки в левом верхнем углу
	QPointF topLeft{m_center.x() - line.length(), m_center.y() - line.length()};

	// Координаты точки в правом нижнем углу
	QPointF bottomRight{m_center.x() + line.length(),
						m_center.y() + line.length()};

	return QRectF{topLeft, bottomRight};
}
