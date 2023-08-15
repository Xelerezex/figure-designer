#include "selectionrectangle.h"

#include <QPainter>

// DEBUG:
#include <QDebug>

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"

SelectionRectangle::SelectionRectangle(QGraphicsItem* parent)
	: FigureBase{parent}
	, m_destination{0.0, 0.0}
{
	qDebug("SelectionRectangle created");
}

SelectionRectangle::~SelectionRectangle()
{
	qDebug("SelectionRectangle deleted");
}

int SelectionRectangle::type() const
{
	return FigureBase::SelectionRectangle;
}

void SelectionRectangle::act(StartDrawing&& startDrawing)
{
	startDrawing.act(this);
}

void SelectionRectangle::act(ContinueDrawing&& continueDrawing)
{
	continueDrawing.act(this);
}

void SelectionRectangle::act(CompleteDrawing&& completeDrawing)
{
	completeDrawing.act(this);
}

QPointF SelectionRectangle::destination() const
{
	return m_destination;
}

void SelectionRectangle::setDestination(QPointF newDestination)
{
	m_destination = newDestination;
}

QRectF SelectionRectangle::boundingRect() const
{
	return countFigure().normalized();
}

void SelectionRectangle::paint(QPainter*					   painter,
							   const QStyleOptionGraphicsItem* option,
							   QWidget*						   widget)
{
	// Не рисуем метод, если не задан режим отрисовки
	if (isNotExisting())
	{
		return;
	}

	Q_UNUSED(option);
	Q_UNUSED(widget);

	// DEBUG:
	qDebug() << "PAINT SELECTIONAL RECTANGLE: "
			 << "center:" << center() << "destination:" << m_destination
			 << "POSITION ON SCENE:" << pos();

	const qreal penWidth{1.5};

	// Класс для отрисовки границы фигуры
	QPen drawingPen{
		Qt::black, penWidth, Qt::DashLine, Qt::FlatCap, Qt::MiterJoin};

	QPainterPath pathTitle;
	pathTitle.setFillRule(Qt::OddEvenFill);

	QRectF frameRect = boundingRect();
	frameRect.setWidth(boundingRect().width() - (penWidth * 4));
	frameRect.setHeight(boundingRect().height() - (penWidth * 4));
	pathTitle.addRect(frameRect);

	painter->setPen(drawingPen);
	painter->drawPath(pathTitle.simplified());
}

QRectF SelectionRectangle::countFigure() const
{
	// Координаты точки в левом верхнем углу
	QPointF topLeft{center().x(), center().y()};

	// Координаты точки в правом нижнем углу
	QPointF bottomRight{m_destination.x(), m_destination.y()};

	return QRectF{topLeft, bottomRight};
}
