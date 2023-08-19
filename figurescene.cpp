#include "figurescene.h"

#include "clicktracker.h"
#include "modificationhandler.h"

#include <QMenu>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

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
		onRightMousePressEvent(mouseEvent);
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
		onRightMouseMoveEvent(mouseEvent);
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
	// Устанавливаем ограничения по Сцене
	const qreal coordX{0};
	const qreal coordY{0};
	const qreal width{5'000};
	const qreal height{5'000};
	setSceneRect(QRectF(coordX, coordY, width, height));

	// Убрано индексирование для оптимизации
	setItemIndexMethod(QGraphicsScene::NoIndex);

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

void FigureScene::onRightMousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	// Координаты Сцены
	const auto sceneCoord = mouseEvent->screenPos();

	m_modificationHandler->startRotation(sceneCoord);
}

void FigureScene::onRightMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	// Координаты Сцены
	const auto sceneCoord = mouseEvent->scenePos();

	m_modificationHandler->continueRotation(sceneCoord);
}

// DEBUG:
#include <QDebug>
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
