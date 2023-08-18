#include "figurehandler.h"

#include "figurecloner.h"
#include "clicktracker.h"
#include "figuregraphicsview.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"

#include <QGraphicsSceneMouseEvent>

#include <QtMath>

FigureHandler::FigureHandler(FigureGraphicsView* parent,
							 ClickTracker*		 clickTracker)
	: QObject{parent}
	, m_parentView{parent}
	, m_currentSquare{nullptr}
	, m_currentRectangle{nullptr}
	, m_currentCircle{nullptr}
	, m_currentTriangle{nullptr}
	, m_clickTracker{clickTracker}

{
}

FigureHandler::~FigureHandler()
{
}

void FigureHandler::addNewSquare(QPointF itemCoord, QPointF sceneCoord)
{
	m_currentSquare = new Square{};
	m_currentSquare->act(StartDrawing{itemCoord, sceneCoord});
	m_parentView->scene()->addItem(m_currentSquare);
}

void FigureHandler::addNewRectangle(QPointF itemCoord, QPointF sceneCoord)
{
	m_currentRectangle = new Rectangle{};
	m_currentRectangle->act(StartDrawing{itemCoord, sceneCoord});
	m_parentView->scene()->addItem(m_currentRectangle);
}

void FigureHandler::addNewCircle(QPointF itemCoord, QPointF sceneCoord)
{
	m_currentCircle = new Circle{};
	m_currentCircle->act(StartDrawing{itemCoord, sceneCoord});
	m_parentView->scene()->addItem(m_currentCircle);
}

void FigureHandler::addNewTriangleDot(QPointF itemCoord, QPointF sceneCoord)
{
	bool isNull{m_currentTriangle == nullptr};

	// Первичное создание треугольника
	if (isNull)
	{
		m_currentTriangle = new Triangle{};
		m_currentTriangle->act(StartDrawing{itemCoord, sceneCoord});
		m_parentView->scene()->addItem(m_currentTriangle);
	}
	// Зануление указателя, если элемент был удален
	else if (!m_currentTriangle->isLineDrawing() && !isNull)
	{
		m_currentTriangle = nullptr;
	}
	// Продолжаем отрисовку. Заканчиваем отрисовку одной точки
	else
	{
		m_currentTriangle->act(CompleteDrawing{itemCoord});

		if (m_currentTriangle->isThirdDrawn())
		{
			m_currentTriangle = nullptr;
		}
	}
}

void FigureHandler::continueDrawingSquare(QPointF itemCoord)
{
	if (m_currentSquare != nullptr)
	{
		m_currentSquare->act(ContinueDrawing{itemCoord});
	}
}

void FigureHandler::continueDrawingRectangle(QPointF coordinate)
{
	if (m_currentRectangle != nullptr)
	{
		m_currentRectangle->act(ContinueDrawing{coordinate});
	}
}

void FigureHandler::continueDrawingCircle(QPointF coordinate)
{
	if (m_currentCircle != nullptr)
	{
		m_currentCircle->act(ContinueDrawing{coordinate});
	}
}

void FigureHandler::continueDrawingTriangle(QPointF coordinate)
{
	if (m_currentTriangle != nullptr)
	{
		m_currentTriangle->act(ContinueDrawing{coordinate});
		// m_parentView->scene()->update();
	}
}

void FigureHandler::completeSquare(QPointF coordinate)
{
	if (m_currentSquare != nullptr)
	{
		m_currentSquare->act(CompleteDrawing{coordinate});
		m_currentSquare = nullptr;
	}
}

void FigureHandler::completeRectangle(QPointF coordinate)
{
	if (m_currentRectangle != nullptr)
	{
		m_currentRectangle->act(CompleteDrawing{coordinate});
		m_currentRectangle = nullptr;
	}
}

void FigureHandler::completeCircle(QPointF coordinate)
{
	if (m_currentCircle != nullptr)
	{
		m_currentCircle->act(CompleteDrawing{coordinate});
		m_currentCircle = nullptr;
	}
}

void FigureHandler::abortDrawing()
{
	if (m_currentSquare != nullptr)
	{
		m_parentView->scene()->removeItem(m_currentSquare);
		m_currentSquare = nullptr;
	}
	if (m_currentRectangle != nullptr)
	{
		m_parentView->scene()->removeItem(m_currentRectangle);
		m_currentRectangle = nullptr;
	}
	if (m_currentCircle != nullptr)
	{
		m_parentView->scene()->removeItem(m_currentCircle);
		m_currentCircle = nullptr;
	}
	if (m_currentTriangle != nullptr)
	{
		handleTriangleRemovement();
	}
}

void FigureHandler::cloneSelectedItems()
{
	const auto& items = m_parentView->scene()->selectedItems();

	// Убираем старые выделения фигур
	unselectAllItems();

	foreach (const auto& item, items)
	{
		if (item->type() == FigureBase::Square)
		{
			auto* square = FigureCloner::cloneSquare(item);
			m_parentView->scene()->addItem(square);
			square->setSelected(true);
		}
		else if (item->type() == FigureBase::Rectangle)
		{
			auto* rectangle = FigureCloner::cloneRectangle(item);
			m_parentView->scene()->addItem(rectangle);
			rectangle->setSelected(true);
		}
		else if (item->type() == FigureBase::Triangle)
		{
			auto* triangle = FigureCloner::cloneTriangle(item);
			m_parentView->scene()->addItem(triangle);
			triangle->setSelected(true);
		}
		else if (item->type() == FigureBase::Circle)
		{
			auto* circle = FigureCloner::cloneCircle(item);
			m_parentView->scene()->addItem(circle);
			circle->setSelected(true);
		}
	}
}

void FigureHandler::handleTriangleRemovement()
{
	bool isShort{false};

	// Координаты метса, гед отпустили мышку в системе координат Фигуры
	QPointF leftMouseReleaseCoordItem
		= m_parentView->mapFromScene(m_clickTracker->lastLeftMouseReleased());

	bool isFirstDrawn = m_currentTriangle->isFirstDrawn();
	if (isFirstDrawn)
	{
		isShort = ClickTracker::isShortDistance(m_currentTriangle->first(),
												leftMouseReleaseCoordItem);
	}

	bool isSecondDrawn = m_currentTriangle->isSecondDrawn();
	if (isSecondDrawn)
	{
		isShort = ClickTracker::isShortDistance(m_currentTriangle->second(),
												leftMouseReleaseCoordItem);
	}

	if (isShort)
	{
		m_currentTriangle->stopDrawingLine();
		m_parentView->scene()->removeItem(m_currentTriangle);
	}
}

void FigureHandler::unselectAllItems() const
{
	foreach (const auto item, m_parentView->scene()->items())
	{
		item->setSelected(false);
	}
}
