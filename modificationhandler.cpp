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

namespace
{
/*!
 * \brief Метод позволяющий определить в какую сторону крутится мыщь,
 *        по часовой или против часовой
 * \param rotationCenter - точка центра вращения фигуры
 * \param previousPoint - точка, где произошло нажатие на правую кнопку
 * \param currentPoint - точка где сейчас стоит мышка после движения
 * \return true - если по часовой
 */
bool isLeft (const QPointF& rotationCenter,
			 const QPointF& previousPoint,
			 const QPointF& currentPoint)
{
	return ((previousPoint.x() - rotationCenter.x())
				* (currentPoint.y() - rotationCenter.y())
			- (previousPoint.y() - rotationCenter.y())
				  * (currentPoint.x() - rotationCenter.x()))
		   > 0;
}
} // namespace

#include <QDebug>
void ModificationHandler::continueRotation(const QPointF& sceneCoord)
{
	QPointF lastRightPressedCoord{m_clickTracker->lastRightMousePressed()};

	foreach (QGraphicsItem* item, m_parentScene->selectedItems())
	{
		QTransform transform;
		QPointF	   center = item->sceneBoundingRect().center();

		transform.translate(center.x(), center.y());

		// Угол на который стоит повернуть Фигуру
		qreal angle{1.25};
		// С этой формулой долгое время не выходило
		// = qAtan2(lastRightPressedCoord.y() - sceneCoord.y(),
		//				   lastRightPressedCoord.x() - sceneCoord.x());
		// Значение PI
		// const qreal piValue{qAtan(1) * 4};
		if (!isLeft(center, lastRightPressedCoord, sceneCoord))
		{
			angle = -qAbs(angle);
		}
		else
		{
			angle = qAbs(angle);
		}

		qDebug() << "Center:" << center << "lastRight" << lastRightPressedCoord
				 << "sceneCoord" << sceneCoord << "isLeft"
				 << isLeft(center, lastRightPressedCoord, sceneCoord) << "Angle"
				 << angle;

		transform.rotate(angle);
		transform.translate(-center.x(), -center.y());

		item->setPos(transform.map(item->pos()));
		item->setRotation(item->rotation() + angle);
	}
	m_clickTracker->setLastRightMousePressed(sceneCoord);
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
