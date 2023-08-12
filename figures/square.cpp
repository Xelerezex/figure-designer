#include "square.h"

#include <QPainter>

// DEBUG:
#include <QDebug>

Square::Square(QGraphicsItem* parent)
	: FigureBase{parent}
	, m_center{0.0, 0.0}
	, m_destination{0.0, 0.0}
{
}

Square::~Square()
{
	// DEBUG:
	qDebug("Square deleted");
}

QPointF Square::center() const
{
	return m_center;
}

void Square::setCenter(QPointF newCenter)
{
	m_center = newCenter;
}

QPointF Square::destination() const
{
	return m_destination;
}

void Square::setDestination(QPointF newDestination)
{
	m_destination = newDestination;
}

QRectF Square::boundingRect() const
{
	return countSquare().normalized();
}

void Square::paint(QPainter*					   painter,
				   const QStyleOptionGraphicsItem* option,
				   QWidget*						   widget)
{
	const qreal penWidth{3};

	// Класс для отрисовки границы фигуры
	QPen drawingPen;

	if (!isFullyCreated())
	{
		drawingPen
			= {Qt::black, penWidth, Qt::DashLine, Qt::FlatCap, Qt::MiterJoin};
	}
	else if (isSelected() && isFullyCreated())
	{
		const int color{13369233};
		drawingPen
			= {Qt::black, penWidth, Qt::DashLine, Qt::FlatCap, Qt::MiterJoin};
		painter->setBrush(QBrush(color));
	}
	if (!isSelected() && isFullyCreated())
	{
		const int color{13369233};
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

	// DEBUG:
	qDebug() << "Length: " << QLineF{m_center, m_destination}.length()
			 << ", Dest: " << m_destination << ", Center: " << m_center;
}

QRectF Square::countSquare() const
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
