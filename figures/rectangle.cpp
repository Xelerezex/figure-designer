#include "rectangle.h"

#include <QPainter>

Rectangle::Rectangle(QGraphicsItem* parent)
	: FigureBase{parent}
{
}

Rectangle::~Rectangle()
{
	// DEBUG:
	qDebug("Rectangle deleted");
}

QPointF Rectangle::center() const
{
	return m_center;
}

void Rectangle::setCenter(QPointF newCenter)
{
	m_center = newCenter;
}

QPointF Rectangle::destination() const
{
	return m_destination;
}

void Rectangle::setDestination(QPointF newDestination)
{
	m_destination = newDestination;
}

QRectF Rectangle::boundingRect() const
{
	return countFigure().normalized();
}

void Rectangle::paint(QPainter*						  painter,
					  const QStyleOptionGraphicsItem* option,
					  QWidget*						  widget)
{
	const qreal penWidth{3};
	const int	color{4501714};

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
	pathTitle.addRect(frameRect);

	painter->setPen(drawingPen);
	painter->drawPath(pathTitle.simplified());
}

QRectF Rectangle::countFigure() const
{
	// Координаты точки в левом верхнем углу
	QPointF topLeft{m_center.x(), m_center.y()};

	// Координаты точки в правом нижнем углу
	QPointF bottomRight{m_destination.x(), m_destination.y()};

	return QRectF{topLeft, bottomRight};
}
