#include "figurehandler.h"

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

FigureHandler::FigureHandler(FigureGraphicsView* parent)
	: QObject{parent}
	, m_parentView{parent}
	, m_currentSquare{nullptr}
	, m_currentRectangle{nullptr}
	, m_currentCircle{nullptr}
	, m_currentTriangle{nullptr}
	, m_clickHandler{new ClickTracker{this}}

{
}

FigureHandler::~FigureHandler()
{
}

void FigureHandler::setLastLeftMousePressed(QPointF pressedCoord)
{
	m_clickHandler->setLastLeftMousePressed(pressedCoord);
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
	if (m_currentTriangle == nullptr)
	{
		m_currentTriangle = new Triangle{};
		m_currentTriangle->act(StartDrawing{itemCoord, sceneCoord});
		m_parentView->scene()->addItem(m_currentTriangle);
	}
	else
	{
		m_currentTriangle->act(CompleteDrawing{itemCoord});

		if (m_currentTriangle->isThirdDrawn())
		{
			m_currentTriangle->setSelected(true);
			m_currentTriangle = nullptr;
		}
	}
}

void FigureHandler::continueDrawingSquare(QPointF itemCoord)
{
	m_currentSquare->act(ContinueDrawing{itemCoord});
	m_parentView->scene()->update();
}

void FigureHandler::continueDrawingRectangle(QPointF coordinate)
{
	m_currentRectangle->act(ContinueDrawing{coordinate});
	m_parentView->scene()->update();
}

void FigureHandler::continueDrawingCircle(QPointF coordinate)
{
	m_currentCircle->act(ContinueDrawing{coordinate});
	m_parentView->scene()->update();
}

void FigureHandler::continueDrawingTriangle(QPointF coordinate)
{
	if (m_currentTriangle == nullptr)
	{
		return;
	}

	m_currentTriangle->act(ContinueDrawing{coordinate});
	m_parentView->scene()->update();
}

void FigureHandler::completeSquare(QPointF coordinate)
{
	m_currentSquare->act(CompleteDrawing{coordinate});
	m_currentSquare = nullptr;
}

void FigureHandler::completeRectangle(QPointF coordinate)
{
	m_currentRectangle->act(CompleteDrawing{coordinate});
	m_currentRectangle = nullptr;
}

void FigureHandler::completeCircle(QPointF coordinate)
{
	m_currentCircle->act(CompleteDrawing{coordinate});
	m_currentCircle = nullptr;
}
