#include "figurescene.h"

#include <QMenu>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

#include "clicktracker.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"

// DEBUG:
#include <QDebug>

FigureScene::FigureScene(QMenu* itemMenu, QObject* parent)
	: QGraphicsScene{parent}
	, m_currentMode{Mode::Modification}
	, m_currentSquare{nullptr}
	, m_currentRectangle{nullptr}
	, m_currentTriangle{nullptr}
	, m_clickHandler{new ClickTracker{this}}
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
	m_clickHandler->setLastLeftMouseClick(mouseEvent->scenePos());

	if (m_currentMode == SquareDraw)
	{
		m_currentSquare = new Square{};
		m_currentSquare->act(StartDrawing{mouseEvent});
		addItem(m_currentSquare);
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_currentRectangle = new Rectangle{};
		m_currentRectangle->act(StartDrawing{mouseEvent});
		addItem(m_currentRectangle);
	}
	else if (m_currentMode == CircleDraw)
	{
		m_currentCircle = new Circle{};
		m_currentCircle->act(StartDrawing{mouseEvent});
		addItem(m_currentCircle);
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
		m_currentSquare->act(ContinueDrawing{mouseEvent});
		update();
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_currentRectangle->act(ContinueDrawing{mouseEvent});
		update();
	}
	else if (m_currentMode == CircleDraw)
	{
		m_currentCircle->act(ContinueDrawing{mouseEvent});
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

void FigureScene::onMouseLeftButtonReleased(
	QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode == SquareDraw)
	{
		m_currentSquare->act(CompleteDrawing{mouseEvent});
		m_currentSquare = nullptr;
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_currentRectangle->act(CompleteDrawing{mouseEvent});
		m_currentRectangle = nullptr;
	}
	else if (m_currentMode == CircleDraw)
	{
		m_currentCircle->act(CompleteDrawing{mouseEvent});
		m_currentCircle = nullptr;
	}
	else if (m_currentMode == TriangleDraw)
	{
		if (m_currentTriangle == nullptr)
		{
			m_currentTriangle = new Triangle{};
			m_currentTriangle->act(StartDrawing{mouseEvent});
			addItem(m_currentTriangle);
		}
		else
		{
			m_currentTriangle->act(CompleteDrawing{mouseEvent});

			if (m_currentTriangle->isThirdDrawn())
			{
				m_currentTriangle->setSelected(true);
				m_currentTriangle = nullptr;
			}
		}
	}

	qDebug("mouseReleaseEvent");

	// Вызов метода базового класса
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void FigureScene::onEmptyMouseMoved(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode == TriangleDraw)
	{
		if (m_currentTriangle == nullptr)
		{
			return;
		}

		m_currentTriangle->act(ContinueDrawing{mouseEvent});
		update();
	}
}
