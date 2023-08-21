#include "selectionrectangle.h"

#include <QPainter>

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"
#include "serializetojson.h"

SelectionRectangle::SelectionRectangle(QMenu* fileMenu, QGraphicsItem* parent)
	: FigureBase{fileMenu, parent}
	, m_destination{0.0, 0.0}
{
}

SelectionRectangle::~SelectionRectangle()
{
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

void SelectionRectangle::act(SerializeToJson&& serialize)
{
	serialize.act(this);
}

const QPointF& SelectionRectangle::leftTop()
{
	return m_leftTop;
}

void SelectionRectangle::setLeftTop(const QPointF& newLeftTop)
{
	m_leftTop = newLeftTop;
}

const QPointF& SelectionRectangle::destination() const
{
	return m_destination;
}

void SelectionRectangle::setDestination(const QPointF& newDestination)
{
	m_destination = newDestination;

	// Сохранить позицию центра, после отрисовки второй точки
	setCenter(boundingRect().center());
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
	return QRectF{m_leftTop, m_destination};
}
