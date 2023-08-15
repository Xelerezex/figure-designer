#include "modificationhandler.h"

#include "clicktracker.h"
#include "figurescene.h"
#include "selectionrectangle.h"

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"

#include <QGraphicsItem>
#include <QApplication>
// DEBUG:
#include <QDebug>

ModificationHandler::ModificationHandler(FigureScene*  parent,
										 ClickTracker* clickTracker)
	: QObject{parent}
	, m_parentScene{parent}
	, m_clickTracker{clickTracker}
	, m_selectionRect{nullptr}
{
}

ModificationHandler::~ModificationHandler()
{
}

bool ModificationHandler::isOnFigure(const QPointF& sceneCoord) const
{
	// updateAllItems();
	// m_parentScene

	// Указатель на фигуру
	QGraphicsItem* figure = m_parentScene->itemAt(sceneCoord, QTransform{});

	// DEBUG:
	if (figure != nullptr)
	{
		qDebug() << "Is on figure:" << (figure != nullptr);
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

void ModificationHandler::selectAllItemsInList(
	const QList<QGraphicsItem*>& list)
{
	foreach (const auto item, list)
	{
		item->setSelected(true);
	}
}

void ModificationHandler::unselectAllItems() const
{
	foreach (const auto item, m_parentScene->items())
	{
		item->setSelected(false);
	}
}

void ModificationHandler::addNewSelectionRectangle(const QPointF& sceneCoord)
{
	if (m_selectionRect == nullptr)
	{
		m_selectionRect = new SelectionRectangle{};
		m_selectionRect->act(StartDrawing{sceneCoord, sceneCoord});
		m_parentScene->addItem(m_selectionRect);
	}
	// m_parentScene->update();
}

void ModificationHandler::continueDrawingSelectionRectangle(
	const QPointF& sceneCoord)
{
	const bool isMouseClicked{m_clickTracker->isLeftMouseClicked(sceneCoord)};

	if (m_selectionRect != nullptr && !isMouseClicked)
	{
		m_selectionRect->act(ContinueDrawing{sceneCoord});
	}
}

void ModificationHandler::completeDrawingSelectionRectangle(
	const QPointF& sceneCoord)
{
	if (m_selectionRect == nullptr)
	{
		return;
	}

	// Если не зажат Ctrl - то снимаем выделение со всех Фигур
	const bool isCtrlNotPressed{
		(QApplication::keyboardModifiers() & Qt::ControlModifier) == 0};
	if (isCtrlNotPressed)
	{
		// Убираем выделение со всех элементов
		unselectAllItems();
	}

	m_selectionRect->act(CompleteDrawing{sceneCoord});

	// Получаем все элементы, которые пересекаются с Прямоугольником
	// Выделения
	const auto& listWithItems
		= m_parentScene->items(m_selectionRect->boundingRect());
	selectAllItemsInList(listWithItems);

	// DEBUG:
	qDebug() << "Selected items:" << listWithItems.size();

	// Удаляем со сцены Прямоугольник
	m_parentScene->removeItem(m_selectionRect);
	delete m_selectionRect;
	m_selectionRect = nullptr;
}

void ModificationHandler::updateSelectedItems() const
{
	foreach (const auto item, m_parentScene->selectedItems())
	{
		item->setSelected(false);
	}
}

void ModificationHandler::updateAllItems() const
{
	foreach (const auto item, m_parentScene->items())
	{
		item->update();
	}
}
