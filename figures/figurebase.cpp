#include "figurebase.h"

FigureBase::FigureBase(QGraphicsItem* parent)
	: QGraphicsItem{parent}
	, m_currentCycle{NotExisting}
	, m_center{0.0, 0.0}
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}

FigureBase::~FigureBase()
{
}

QPointF FigureBase::center() const
{
	return m_center;
}

void FigureBase::setCenter(QPointF newCenter)
{
	m_center = newCenter;
}

void FigureBase::startCreating()
{
	m_currentCycle = Creating;
}

void FigureBase::completeCreating()
{
	m_currentCycle = FullyCreated;
}

bool FigureBase::isFullyCreated() const
{
	return m_currentCycle == FullyCreated;
}
