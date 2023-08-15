#include "modificationhandler.h"

#include "clicktracker.h"
#include "figuregraphicsview.h"

#include <QGraphicsItem>
// DEBUG:
#include <QDebug>

ModificationHandler::ModificationHandler(FigureGraphicsView* parent,
										 ClickTracker*		 clickTracker)
	: QObject{parent}
	, m_parentView{parent}
	, m_clickTracker{clickTracker}
{
}

ModificationHandler::~ModificationHandler()
{
}

void ModificationHandler::modificateOnLeftButtonPressed(
	const QPoint& coordPress)
{
	QGraphicsItem* figure = m_parentView->itemAt(coordPress);

	// Была ли нажата кнопка над фигурой
	if (figure != nullptr)
	{
		// DEBUG:
		qDebug() << "Modification pressed left on figure: " << figure->type();

		unselectAllItems();
		figure->setSelected(true);
	}
}

void ModificationHandler::modificateOnLeftButtonClicked(
	const QPoint& coordPress)
{
	QGraphicsItem* figure = m_parentView->itemAt(coordPress);
	// Находится ли в данный момент мыщь над фигурой
	const bool isUnderFigure{figure != nullptr};
	// Произошел ли клик мыщи
	const bool isMouseClicked{m_clickTracker->isLeftMouseClicked(
		m_clickTracker->lastLeftMouseReleased())};

	if (isMouseClicked && !isUnderFigure)
	{
		// DEBUG:
		qDebug() << "Left Mouse Clicked";

		unselectAllItems();
	}
	else
	{
		qDebug("No Click");
	}
}

void ModificationHandler::modificateOnLeftMouseAndCtrl(const QPoint& coordPress)

{
	QGraphicsItem* figure = m_parentView->itemAt(coordPress);

	// Находится ли в данный момент мыщь над фигурой
	const bool isUnderFigure{figure != nullptr};

	if (isUnderFigure)
	{
		figure->setSelected(true);
	}
}

void ModificationHandler::unselectAllItems() const
{
	foreach (const auto item, m_parentView->items())
	{
		item->setSelected(false);
	}
}
