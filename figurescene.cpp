#include "figurescene.h"

#include <QMenu>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

#include "figurehandler.h"

// DEBUG:
#include <QDebug>

FigureScene::FigureScene(/*QMenu* itemMenu, */ QObject* parent)
	: QGraphicsScene{parent}
	, m_currentMode{Mode::Modification}
	, m_figureHandler{new FigureHandler{this}}

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

bool FigureScene::isTriangleMode() const
{
	return m_currentMode == TriangleDraw;
}

void FigureScene::setCurrentMode(Mode newCurrentMode)
{
	m_currentMode = newCurrentMode;
}

void FigureScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->button() == Qt::LeftButton)
	{
		onMouseLeftButtonPressed(mouseEvent);
	}
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	// true - только если движение с зажатой левой кнопокой мыщи
	bool onlyWithLeftButtonMove{
		static_cast<bool>(mouseEvent->buttons() & Qt::LeftButton)};

	// true - если движение мыщи без зажатых кнопок
	bool onlyMouseMove{mouseEvent->buttons() == Qt::NoButton};

	if (onlyWithLeftButtonMove)
	{
		onMouseLeftButtonMoved(mouseEvent);
	}

	if (onlyMouseMove && isTriangleMode())
	{
		onEmptyMouseMoved(mouseEvent);
	}
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->button() == Qt::LeftButton)
	{
		onMouseLeftButtonReleased(mouseEvent);
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

	// Устанавливаем имя объекта класса
	setObjectName(QLatin1String("FigureScene"));

	// setMouseTracking
}

void FigureScene::onMouseLeftButtonPressed(QGraphicsSceneMouseEvent* mouseEvent)
{
	// Запоминаем место, где произошло нажатие
	m_figureHandler->setLastLeftMousePressed(mouseEvent->scenePos());

	if (m_currentMode == SquareDraw)
	{
		m_figureHandler->addNewSquare(mouseEvent->scenePos());
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_figureHandler->addNewRectangle(mouseEvent->scenePos());
	}
	else if (m_currentMode == CircleDraw)
	{
		m_figureHandler->addNewCircle(mouseEvent->scenePos());
	}
	else if (m_currentMode == TriangleDraw)
	{
	}

	qDebug("mousePressEvent");

	// Вызов метода базового класса
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void FigureScene::onMouseLeftButtonMoved(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode == SquareDraw)
	{
		m_figureHandler->continueDrawingSquare(mouseEvent->scenePos());
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_figureHandler->continueDrawingRectangle(mouseEvent->scenePos());
	}
	else if (m_currentMode == CircleDraw)
	{
		m_figureHandler->continueDrawingCircle(mouseEvent->scenePos());
	}
	else if (m_currentMode == Modification)
	{
		// TODO: Сделать обновление координат фигуры, в режиме передвижения
		// Вызов метода базового класса
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}

	qDebug("mouseMoveEvent");
}

void FigureScene::onMouseLeftButtonReleased(
	QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode == SquareDraw)
	{
		m_figureHandler->completeSquare(mouseEvent->scenePos());
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_figureHandler->completeRectangle(mouseEvent->scenePos());
	}
	else if (m_currentMode == CircleDraw)
	{
		m_figureHandler->completeCircle(mouseEvent->scenePos());
	}
	else if (m_currentMode == TriangleDraw)
	{
		m_figureHandler->addNewTriangleDot(mouseEvent->scenePos());
	}

	qDebug("mouseReleaseEvent");

	// Вызов метода базового класса
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void FigureScene::onEmptyMouseMoved(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode == TriangleDraw)
	{
		m_figureHandler->continueDrawingTriangle(mouseEvent->scenePos());
	}
}
