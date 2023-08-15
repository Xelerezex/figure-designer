#include "figurescene.h"

#include "clicktracker.h"
#include "modificationhandler.h"

#include <QMenu>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
// DEBUG:
#include <QDebug>

#include "rectangle.h"

FigureScene::FigureScene(/*QMenu* itemMenu, */ QObject* parent)
	: QGraphicsScene{parent}
	, m_currentMode{Mode::Modification}
	, m_clickTracker{new ClickTracker{this}}
	, m_modificationHandler{new ModificationHandler{this, m_clickTracker}}
{
	// Настраиваем сцену
	setupFigureScene();
}

FigureScene::~FigureScene()
{
}

FigureScene::Mode FigureScene::currentMode() const
{
	// DEBUG:
	qDebug() << m_currentMode;
	return m_currentMode;
}

void FigureScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	// Нажата ли Левая кнопка мыщи
	const bool isLeftButton{mouseEvent->button() == Qt::LeftButton};
	// Нажата ли Правая кнопка мыщи
	const bool isRightButtonPressed{mouseEvent->button() == Qt::RightButton};

	if (isLeftButton)
	{
		onLeftMousePressEvent(mouseEvent);
	}
	else if (isRightButtonPressed)
	{
		// Указатель на фигуру
		Rectangle* figure = qgraphicsitem_cast<Rectangle*>(
			itemAt(mouseEvent->scenePos(), QTransform{}));
		if (figure != nullptr)
		{
			figure->setTransformOriginPoint(figure->center());
			qDebug("Right button pressed");
		}
	}
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	// true - только если движение с зажатой левой кнопокой мыщи
	bool onlyWithLeftButtonMove{
		static_cast<bool>(mouseEvent->buttons() & Qt::LeftButton)};
	// true - только если движение с зажатой правой кнопокой мыщи
	bool onlyWithRightButtonMove{
		static_cast<bool>(mouseEvent->buttons() & Qt::RightButton)};

	if (onlyWithLeftButtonMove)
	{
		onLeftMouseMoveEvent(mouseEvent);
	}
	else if (onlyWithRightButtonMove)
	{
		// Указатель на фигуру
		Rectangle* figure = qgraphicsitem_cast<Rectangle*>(
			itemAt(mouseEvent->scenePos(), QTransform{}));
		if (figure != nullptr)
		{
			figure->setRotation(-45); //(figure->center());
			qDebug("Right button pressed");
		}
		//  Прокидываем зажатие + движение Правой кнопки на сцену
		qDebug("Right button pressed & move");
	}

	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	// Отжата ли Левая кнопка мыщи
	const bool isLeftButtonReleased{mouseEvent->button() == Qt::LeftButton};

	if (isLeftButtonReleased)
	{
		onLeftMouseReleaseEvent(mouseEvent);
	}

	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void FigureScene::keyReleaseEvent(QKeyEvent* event)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	if (event->key() == Qt::Key_D)
	{
		handleSelectedDelete();
	}
}

void FigureScene::setupFigureScene()
{
	// DEBUG:
	setItemIndexMethod(QGraphicsScene::NoIndex);

	// Устанавливаем ограничения по Сцене
	const qreal coordX{0};
	const qreal coordY{0};
	const qreal width{5'000};
	const qreal height{5'000};
	setSceneRect(QRectF(coordX, coordY, width, height));

	// Устанавливаем имя объекта класса
	setObjectName(QLatin1String("FigureScene"));
}

void FigureScene::setCurrentMode(Mode newCurrentMode)
{
	m_currentMode = newCurrentMode;
	// При переключении Режимов - выбор Фигур должен спадать
	m_modificationHandler->unselectAllItems();
}

void FigureScene::onLeftMousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	// Обновляем отрисовку сцены
	update();

	// Координаты эвента на Сцене
	const QPointF sceneCoord = mouseEvent->scenePos();

	// Произвести действие по нажатию левой кнопки мыщи
	m_modificationHandler->modificateOnLeftMousePressed(sceneCoord);

	// Пробросить дальше эвент, если нажатие произошло над фигурой
	if (!m_modificationHandler->isOnFigure(sceneCoord))
	{
		m_modificationHandler->addNewSelectionRectangle(sceneCoord);
	}
	else
	{
		QGraphicsScene::mousePressEvent(mouseEvent);
	}
}

void FigureScene::onLeftMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	// Обновляем отрисовку сцены
	update();

	// Координаты эвента на Сцене
	const QPointF sceneCoord = mouseEvent->scenePos();

	//  Продолжать отрисовку Прямоугольника выделения
	m_modificationHandler->continueDrawingSelectionRectangle(sceneCoord);
}

void FigureScene::onLeftMouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	// Координаты эвента на Сцене
	const QPointF sceneCoord = mouseEvent->scenePos();

	// Завершить отрисовку прямоугольника выделения, если он создан
	m_modificationHandler->completeDrawingSelectionRectangle(sceneCoord);

	if (!m_modificationHandler->isOnFigure(sceneCoord))
	{
		m_modificationHandler->modificateOnLeftMouseReleased(sceneCoord);
	}
}

void FigureScene::handleSelectedDelete()
{
	// DEBUG:
	qDebug() << "Deleted" << selectedItems().size() << "items";

	foreach (auto* item, selectedItems())
	{
		removeItem(item);
		delete item;
	}

	// DEBUG:
	qDebug() << "Elements remained" << items().size();
}
