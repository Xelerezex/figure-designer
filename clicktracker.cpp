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

QPointF ClickTracker::lastLeftMousePressed() const
{
	return m_lastLeftMousePressed;
}

void ClickTracker::setLastLeftMousePressed(QPointF newLastLeftMousePressed)
{
	m_lastLeftMousePressed = newLastLeftMousePressed;
}

QPointF ClickTracker::lastLeftMouseReleased() const
{
	return m_lastLeftMouseReleased;
}

void ClickTracker::setLastLeftMouseReleased(QPointF newLastLeftMouseReleased)
{
	m_lastLeftMouseReleased = newLastLeftMouseReleased;
}

// TODO: Потенциально назвать этот метод isClicke и просто описать, что типа
// кликом считается все то, что не вышло за рамки выделенного нами круга
// И зделать второй метод, который будет трекать - не слишком ли маленькая
// фигура отрисовалась
bool ClickTracker::isLeftMouseClicked(QPointF newLeftMouseRelease)
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

bool ClickTracker::isShortDistance(QPointF first, QPointF second)
{
	const QLineF line{first, second};
	const qreal	 trashHold{10};
	const qreal	 trashHoldDistance{trashHold * 3};

	// DEBUG:
	qDebug() << "FIRST: " << first << "SECOND: " << second
			 << "LENGTH:" << line.length() << "TRASH:" << trashHoldDistance;

	return line.length() < trashHoldDistance;
}
