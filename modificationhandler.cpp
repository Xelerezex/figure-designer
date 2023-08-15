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

bool ModificationHandler::isOnFigure(const QPointF& sceneCoord) const
{
	// Указатель на фигуру
	QGraphicsItem* figure = m_parentScene->itemAt(sceneCoord, QTransform{});

	// DEBUG:
	if (figure != nullptr)
	{
		qDebug() << "Item at" << sceneCoord << "is" << figure->type();
	}

	return figure != nullptr;
}

void ModificationHandler::modificateOnLeftMousePressed(
	const QPointF& sceneCoord)
{
	// Устанавливаем координату последнего нажатия левой кнопки мыши
	m_clickTracker->setLastLeftMousePressed(sceneCoord);

	// DEBUG:
	qDebug() << "Pressed at:" << sceneCoord;
}

void ModificationHandler::modificateOnLeftMouseReleased(
	const QPointF& sceneCoord)
{
	// Устанавливаем координату последнего отпуска левой кнопки мыши
	m_clickTracker->setLastLeftMouseReleased(sceneCoord);

	// Произошел ли клик
	const bool isClicked{m_clickTracker->isLeftMouseClicked()};

	if (isClicked && !isOnFigure(sceneCoord))
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
