#include "rectangle.h"

#include <QPainter>

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"
#include "serializetojson.h"

Rectangle::Rectangle(QMenu* fileMenu, QGraphicsItem* parent)
	: FigureBase{fileMenu, parent}
	, m_leftTop{0.0, 0.0}
	, m_destination{0.0, 0.0}
{
}

Rectangle::~Rectangle()
{
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

void Rectangle::act(SerializeToJson&& serialize)
{
	serialize.act(this);
}

const QPointF& Rectangle::leftTop()
{
	return m_leftTop;
}

void Rectangle::setLeftTop(const QPointF& newLeftTop)
{
	m_leftTop = newLeftTop;
}

const QPointF& Rectangle::destination() const
{
	return m_destination;
}

void Rectangle::setDestination(const QPointF& newDestination)
{
	m_destination = newDestination;

	// Сохранить позицию центра, после отрисовки второй точки
	setCenter(boundingRect().center());
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
	return QRectF{m_leftTop, m_destination};
}
