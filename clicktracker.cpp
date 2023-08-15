#include "clicktracker.h"

#include <QLineF>

ClickTracker::ClickTracker(QObject* parent)
	: QObject{parent}
	, m_lastLeftMousePressed{0.0, 0.0}
	, m_lastLeftMouseReleased{0.0, 0.0}
{
}

ClickTracker::~ClickTracker()
{
}

const QPointF& ClickTracker::lastLeftMousePressed() const
{
	return m_lastLeftMousePressed;
}

void ClickTracker::setLastLeftMousePressed(
	const QPointF& newLastLeftMousePressed)
{
	m_lastLeftMousePressed = newLastLeftMousePressed;

	// Зануляем координату Отпуска Кнопки
	m_lastLeftMouseReleased = QPointF{0.0, 0.0};
}

const QPointF& ClickTracker::lastLeftMouseReleased() const
{
	return m_lastLeftMouseReleased;
}

void ClickTracker::setLastLeftMouseReleased(
	const QPointF& newLastLeftMouseReleased)
{
	m_lastLeftMouseReleased = newLastLeftMouseReleased;
}

bool ClickTracker::isLeftMouseClicked(const QPointF& newLeftMouseRelease)
{
	// Вычисляем так ли далеко была отпущена мыщь относительно места нажатия
	const QPointF distance = newLeftMouseRelease - m_lastLeftMousePressed;
	const qreal	  trashHold{10};

	const qreal	  distanceSpace{distance.x() * distance.x()
								+ distance.y() * distance.y()};
	const qreal	  trashHoldDistance{trashHold * trashHold};

	return distanceSpace < trashHoldDistance;
}

// DEBUG:
#include <QDebug>

bool ClickTracker::isShortDistance(const QPointF& first, const QPointF& second)
{
	const QLineF line{first, second};
	const qreal	 trashHold{10};
	const qreal	 trashHoldDistance{trashHold * 3};

	// DEBUG:
	qDebug() << "FIRST: " << first << "SECOND: " << second
			 << "LENGTH:" << line.length() << "TRASH:" << trashHoldDistance;

	return line.length() < trashHoldDistance;
}
