#include "circle.h"

#include <QPainter>

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"

Circle::Circle(QGraphicsItem* parent)
	: FigureBase{parent}
	, m_destination{0.0, 0.0}
{
}

Circle::~Circle()
{
}

int Circle::type() const
{
	return FigureBase::Circle;
}

void Circle::act(StartDrawing&& startDrawing)
{
	startDrawing.act(this);
}

void Circle::act(ContinueDrawing&& continueDrawing)
{
	continueDrawing.act(this);
}

void Circle::act(CompleteDrawing&& completeDrawing)
{
	completeDrawing.act(this);
}

const QPointF& Circle::destination() const
{
	return m_destination;
}

void Circle::setDestination(const QPointF& newDestination)
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
	Q_UNUSED(option);
	Q_UNUSED(widget);

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
	QLineF line{center(), m_destination};

	// Координаты точки в левом верхнем углу
	QPointF topLeft{center().x() - line.length(), center().y() - line.length()};

	// Координаты точки в правом нижнем углу
	QPointF bottomRight{center().x() + line.length(),
						center().y() + line.length()};

	return QRectF{topLeft, bottomRight};
}
