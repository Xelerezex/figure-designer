#include "figurescene.h"

#include "clicktracker.h"
#include "modificationhandler.h"

#include <QMenu>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
// DEBUG:
#include <QDebug>

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

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	update();

	// Координаты эвента на Сцене
	const QPointF sceneCoord = mouseEvent->scenePos();

	if (!m_modificationHandler->isOnFigure(sceneCoord))
	{
		// Продолжать отрисовку Прямоугольника выделения
		m_modificationHandler->continueDrawingSelectionRectangle(sceneCoord);
	}

	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	// Координаты эвента на Сцене
	const QPointF sceneCoord = mouseEvent->scenePos();

	// Завершить отрисовку прямоугольника выделения, если он создан
	m_modificationHandler->completeDrawingSelectionRectangle(sceneCoord);

	if (!m_modificationHandler->isOnFigure(sceneCoord))
	{
		m_modificationHandler->modificateOnLeftMouseReleased(sceneCoord);
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
