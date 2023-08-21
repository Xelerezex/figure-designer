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
#include <QMenu>

ModificationHandler::ModificationHandler(QMenu*		   fileMenu,
										 ClickTracker* clickTracker,
										 FigureScene*  parent)
	: QObject{parent}
	, m_pFileMenu{fileMenu}
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
	// Указатель на фигуру
	QGraphicsItem* figure = m_parentScene->itemAt(sceneCoord, QTransform{});

	return figure != nullptr;
}

void ModificationHandler::modificateOnLeftMousePressed(
	const QPointF& sceneCoord)
{
	// Устанавливаем координату последнего нажатия левой кнопки мыши
	m_clickTracker->setLastLeftMousePressed(sceneCoord);
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
		m_selectionRect = new SelectionRectangle{m_pFileMenu};
		m_selectionRect->act(StartDrawing{sceneCoord, sceneCoord});
		m_parentScene->addItem(m_selectionRect);
	}
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

void ModificationHandler::startRotation(const QPoint& coordinate)
{
	// Установить первичное значение для начала вращения
	m_clickTracker->setLastRightMousePressed(coordinate);
}

qreal findAngle (QLineF first, QLineF second)
{
	QPointF firstLineStart = {first.x1(), first.y1()};
	QPointF firstLineEnd   = {first.x2(), first.y2()};

	QPointF secondLineStart = {second.x1(), second.y1()};
	QPointF secondLineEnd	= {second.x2(), second.y2()};

	qreal	angle1 = atan2(firstLineStart.y() - firstLineEnd.y(),
						   firstLineStart.x() - firstLineEnd.x());
	qreal	angle2 = atan2(secondLineStart.y() - secondLineEnd.y(),
						   secondLineStart.x() - secondLineEnd.x());

	qreal	resultAngle = (angle2 - angle1) * 180 / M_PI;
	if (resultAngle < 0)
	{
		resultAngle += 360;
	}

	return resultAngle;
}

/*!
 * \brief Данная функция - это попытка сделать правильное вращениеи объект, но
 *        она провалилась
 */
qreal getAngle (QPointF center, QPointF oldPosition, QPointF newPosition)
{
	qreal x1 = oldPosition.x() - center.x();
	qreal y1 = oldPosition.y() - center.y();
	qreal x2 = newPosition.x() - center.x();
	qreal y2 = newPosition.y() - center.y();
	qreal d1 = qSqrt(x1 * x1 + y1 * y1);
	qreal d2 = qSqrt(x2 * x2 + y2 * y2);

	return qAsin((x1 / d1) * (y2 / d2) - (y1 / d1) * (x2 / d2));
}

#include <QDebug>
void ModificationHandler::continueRotation(const QPointF& sceneCoord)
{
	QPointF lastRightPressedCoord{m_clickTracker->lastRightMousePressed()};

	// Раньше все фигуры крутились рядом с одним общим центром
	// QPointF	   center = getUnitedSelectedCenter();

	foreach (QGraphicsItem* item, m_parentScene->selectedItems())
	{
		QTransform transform;
		QPointF	   center = item->sceneBoundingRect().center();

		transform.translate(center.x(), center.y());

		qreal angle = qAtan2(lastRightPressedCoord.y() - sceneCoord.y(),
							 lastRightPressedCoord.x() - sceneCoord.x());

		qDebug() << angle;
		// qreal angle = getAngle(center, lastRightPressedCoord, sceneCoord);
		// if (angle < 0)
		//{
		//	angle *= -1;
		//}

		transform.rotate(angle);
		transform.translate(-center.x(), -center.y());

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
