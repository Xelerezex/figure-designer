#include "figurescene.h"

#include <QMenu>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

#include "square.h"
#include "rectangle.h"

// DEBUG:
#include <QDebug>

FigureScene::FigureScene(QMenu* itemMenu, QObject* parent)
	: QGraphicsScene{parent}
	, m_currentMode{Mode::Modification}
	, m_currentSquare{nullptr}
	, m_currentRectangle{nullptr}
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

void FigureScene::setCurrentMode(Mode newCurrentMode)
{
	m_currentMode = newCurrentMode;
}

void FigureScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
		return;

	if (m_currentMode == SquareDraw)
	{
		m_currentSquare = new Square{};
		m_currentSquare->startCreating();
		m_currentSquare->setCenter(mouseEvent->scenePos());
		m_currentSquare->setDestination(mouseEvent->scenePos()
										+ QPointF{0.1, 0.1});
		addItem(m_currentSquare);
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_currentRectangle = new Rectangle{};
		m_currentRectangle->startCreating();
		m_currentRectangle->setCenter(mouseEvent->scenePos());
		m_currentRectangle->setDestination(mouseEvent->scenePos()
										   + QPointF{0.1, 0.1});
		addItem(m_currentRectangle);
	}

	qDebug("mousePressEvent");

	// Вызов метода базового класса
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	bool onlyLeftButton = mouseEvent->buttons() & Qt::LeftButton;
	if (!onlyLeftButton)
	{
		return;
	}

	if (m_currentMode == SquareDraw)
	{
		m_currentSquare->setDestination(mouseEvent->scenePos());
		update();
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_currentRectangle->setDestination(mouseEvent->scenePos());
		update();
	}
	else if (m_currentMode == Modification)
	{
		// TODO: Сделать обновление координат фигуры, в режиме передвижения
		// Вызов метода базового класса
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}

	qDebug("mouseMoveEvent");
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
		return;

	if (m_currentMode == SquareDraw)
	{
		m_currentSquare->setDestination(mouseEvent->scenePos());
		m_currentSquare->completeCreating();
		m_currentSquare->update();
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_currentRectangle->setDestination(mouseEvent->scenePos());
		m_currentRectangle->completeCreating();
		m_currentRectangle->update();
	}

	qDebug("mouseReleaseEvent");

	// Вызов метода базового класса
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void FigureScene::setupFigureScene()
{
	// Устанавливаем ограничения по Сцене
	const qreal coordX{0};
	const qreal coordY{0};
	const qreal width{5'000};
	const qreal height{5'000};
	setSceneRect(QRectF(coordX, coordY, width, height));

	// Устанавливаем имя объекта класса
	setObjectName(QLatin1String("FigureScene"));
}
