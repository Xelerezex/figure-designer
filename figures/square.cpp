#include "square.h"

#include <QPainter>

// DEBUG:
#include <QDebug>

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"

Square::Square(QGraphicsItem* parent)
	: FigureBase{parent}
	, m_destination{0.0, 0.0}
{
}

Square::~Square()
{
	// DEBUG:
	qDebug("Square deleted");
}

int Square::type() const
{
	return FigureBase::Square;
}

void Square::act(StartDrawing&& startDrawing)
{
	startDrawing.act(this);
}

void Square::act(ContinueDrawing&& continueDrawing)
{
	continueDrawing.act(this);
}

void Square::act(CompleteDrawing&& completeDrawing)
{
	completeDrawing.act(this);
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
	return countFigure().normalized();
}

void Square::paint(QPainter*					   painter,
				   const QStyleOptionGraphicsItem* option,
				   QWidget*						   widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	const qreal penWidth{3};
	const int	color{13369233};

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

	// DEBUG:
	qDebug() << "PAINT SQUARE: "
			 << "center:" << center() << "destination:" << m_destination
			 << "POSITION ON SCENE:" << pos();

	painter->setPen(drawingPen);
	painter->drawPath(pathTitle.simplified());
}

QRectF Square::countFigure() const
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
