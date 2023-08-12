#include "figurebase.h"

FigureBase::FigureBase(QGraphicsItem* parent)
	: QGraphicsItem{parent}
	, m_currentCycle{NotExisting}
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}

FigureBase::~FigureBase()
{
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
