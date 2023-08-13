#include "clicktracker.h"

#include <QGraphicsSceneMouseEvent>

// DEBUG:
#include <QDebug>

ClickTracker::ClickTracker(QObject* parent)
	: QObject{parent}
{
}

ClickTracker::~ClickTracker()
{
	qDebug("ClickTracker deleted");
}

QPointF ClickTracker::lastLeftMouseClick() const
{
	return m_lastLeftMouseClick;
}

void ClickTracker::setLastLeftMouseClick(QPointF newLastLeftMouseClick)
{
	m_lastLeftMouseClick = newLastLeftMouseClick;
}

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
