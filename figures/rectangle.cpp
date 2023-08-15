#include "rectangle.h"

#include <QPainter>

// DEBUG:
#include <QDebug>

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"

Rectangle::Rectangle(QGraphicsItem* parent)
	: FigureBase{parent}
	, m_destination{0.0, 0.0}
{
}

Rectangle::~Rectangle()
{
	// DEBUG:
	qDebug("Rectangle deleted");
}

int Rectangle::type() const
{
	return FigureBase::Rectangle;
}

void Rectangle::act(StartDrawing&& startDrawing)
{
	startDrawing.act(this);
}

void Rectangle::act(ContinueDrawing&& continueDrawing)
{
	continueDrawing.act(this);
}

void Rectangle::act(CompleteDrawing&& completeDrawing)
{
	completeDrawing.act(this);
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
	Q_UNUSED(option);
	Q_UNUSED(widget);

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

	// DEBUG:
	qDebug() << "PAINT RECTANGLE: "
			 << "center:" << center() << "destination:" << m_destination
			 << "POSITION ON SCENE:" << pos();

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
	QPointF topLeft{center().x(), center().y()};

	// Координаты точки в правом нижнем углу
	QPointF bottomRight{m_destination.x(), m_destination.y()};

	return QRectF{topLeft, bottomRight};
}
