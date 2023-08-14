#include "clicktracker.h"

#include <QGraphicsSceneMouseEvent>

ClickTracker::ClickTracker(QObject* parent)
	: QObject{parent}
{
}

ClickTracker::~ClickTracker()
{
}

QPointF ClickTracker::lastLeftMouseClick() const
{
	return m_lastLeftMouseClick;
}

void ClickTracker::setLastLeftMousePressed(QPointF newLastLeftMouseClick)
{
	m_lastLeftMouseClick = newLastLeftMouseClick;
}

// TODO: Потенциально назвать этот метод isClicke и просто описать, что типа
// кликом считается все то, что не вышло за рамки выделенного нами круга
// И зделать второй метод, который будет трекать - не слишком ли маленькая
// фигура отрисовалась
bool ClickTracker::isDistClickReleaseLeftMouseOk(QPointF newLeftMouseRelease)
{
	// Вычисляем так ли далеко была отпущена мыщь относительно места нажатия
	QPointF distance  = newLeftMouseRelease - m_lastLeftMouseClick;
	qreal	trashHold = 10;

	qreal	distanceSpace{distance.x() * distance.x()
						  + distance.y() * distance.y()};
	qreal	trashHoldSpace{trashHold * trashHold};

	return distanceSpace < trashHoldSpace;
}
