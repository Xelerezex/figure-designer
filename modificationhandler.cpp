#include "modificationhandler.h"

#include "clicktracker.h"
#include "figurescene.h"
#include "selectionrectangle.h"

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"

#include <QGraphicsItem>
#include <QApplication>
#include <QtMath>
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

	// Указатель на фигуру
	QGraphicsItem* figure = m_parentScene->itemAt(sceneCoord, QTransform{});
	// Устанавливаем выбранную площадь
	if (figure != nullptr)
	{
		// QPainterPath selectionPath;
		// selectionPath.addRect(figure->boundingRect());
		// m_parentScene->setSelectionArea(selectionPath, QTransform{});
	}

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
	// m_parentScene->setSelectionArea({}, QTransform{});
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

	// QPainterPath selectionPath;
	// selectionPath.addRect(m_selectionRect->boundingRect());
	// m_parentScene->setSelectionArea(selectionPath, QTransform{});

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

void ModificationHandler::startRotation(const QPoint& coordinate)
{
	// Установить первичное значение для начала вращения
	m_clickTracker->setLastRightMousePressed(coordinate);
}

void ModificationHandler::continueRotation(const QPoint& sceneCoord)
{
	QPointF	   lastRightPressedCoord{m_clickTracker->lastRightMousePressed()};

	QPointF	   center = getUnitedSelectedCenter();
	QTransform transform;
	transform.translate(center.x(), center.y());

	qreal angle = qAtan2(lastRightPressedCoord.y() - sceneCoord.y(),
						 lastRightPressedCoord.x() - sceneCoord.x());

	transform.rotate(angle);
	transform.translate(-center.x(), -center.y());

	foreach (QGraphicsItem* item, m_parentScene->selectedItems())
	{
		item->setPos(transform.map(item->pos()));
		item->setRotation(item->rotation() + angle);
	}
}

QRectF ModificationHandler::getUnitedSelectedBoundingRect() const
{
	QRectF				  selectedBoundingRect;
	QList<QGraphicsItem*> selectedItems = m_parentScene->selectedItems();
	foreach (QGraphicsItem* current, selectedItems)
	{
		selectedBoundingRect
			= selectedBoundingRect.united(current->sceneBoundingRect());
	}
	return selectedBoundingRect;
}

QPointF ModificationHandler::getUnitedSelectedCenter() const
{
	return getUnitedSelectedBoundingRect().center();
}
