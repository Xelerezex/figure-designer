#include "modificationhandler.h"

#include "clicktracker.h"
#include "figurescene.h"

#include <QGraphicsItem>
// DEBUG:
#include <QDebug>

ModificationHandler::ModificationHandler(FigureScene*  parent,
										 ClickTracker* clickTracker)
	: QObject{parent}
	, m_parentScene{parent}
	, m_clickTracker{clickTracker}
{
}

ModificationHandler::~ModificationHandler()
{
}

void ModificationHandler::modificateOnLeftMouseReleased(
	const QPointF& sceneCoord)
{
	// Устанавливаем координату последнего отпуска левой кнопки мыши
	m_clickTracker->setLastLeftMouseReleased(sceneCoord);

	// Указатель на фигуру
	QGraphicsItem* figure = m_parentScene->itemAt(sceneCoord, QTransform{});

	// Произошел ли клик
	const bool isClicked{m_clickTracker->isLeftMouseClicked()};
	// Произошел ли отпуск левой кнопки мыши над фигурой
	const bool isOnFigure{figure != nullptr};

	if (isClicked && !isOnFigure)
	{
		qDebug() << "Clicked at:" << sceneCoord;
		unselectAllItems();
	}
}

void ModificationHandler::unselectAllItems() const
{
	foreach (const auto item, m_parentScene->items())
	{
		item->setSelected(false);
	}
}
