#include "figurehandler.h"

#include "figurescene.h"
#include "clicktracker.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

#include "startdrawing.h"
#include "continuedrawing.h"
#include "completedrawing.h"

#include <QGraphicsSceneMouseEvent>

FigureHandler::FigureHandler(FigureScene* parent)
	: QObject{parent}
	, m_parentScene{parent}
	, m_currentSquare{nullptr}
	, m_currentRectangle{nullptr}
	, m_currentCircle{nullptr}
	, m_currentTriangle{nullptr}
	, m_clickHandler{new ClickTracker{this}}

{
}

FigureHandler::~FigureHandler()
{
	// DEBUG:
	qDebug("FigureHandler propperly deleted");
}

void FigureHandler::setLastLeftMousePressed(QPointF pressedCoord)
{
	m_clickHandler->setLastLeftMousePressed(pressedCoord);
}

void FigureHandler::addNewSquare(QPointF coordinate)
{
	m_currentSquare = new Square{};
	m_currentSquare->act(StartDrawing{coordinate});
	m_parentScene->addItem(m_currentSquare);
}

void FigureHandler::addNewRectangle(QPointF coordinate)
{
	m_currentRectangle = new Rectangle{};
	m_currentRectangle->act(StartDrawing{coordinate});
	m_parentScene->addItem(m_currentRectangle);
}

void FigureHandler::addNewCircle(QPointF coordinate)
{
	m_currentCircle = new Circle{};
	m_currentCircle->act(StartDrawing{coordinate});
	m_parentScene->addItem(m_currentCircle);
}

void FigureHandler::addNewTriangleDot(QPointF coordinate)
{
	if (m_currentTriangle == nullptr)
	{
		m_currentTriangle = new Triangle{};
		m_currentTriangle->act(StartDrawing{coordinate});
		m_parentScene->addItem(m_currentTriangle);
	}
	else
	{
		m_currentTriangle->act(CompleteDrawing{coordinate});

		if (m_currentTriangle->isThirdDrawn())
		{
			m_currentTriangle->setSelected(true);
			m_currentTriangle = nullptr;
		}
	}
}

void FigureHandler::continueDrawingSquare(QPointF coordinate)
{
	m_currentSquare->act(ContinueDrawing{coordinate});
	m_parentScene->update();
}

void FigureHandler::continueDrawingRectangle(QPointF coordinate)
{
	m_currentRectangle->act(ContinueDrawing{coordinate});
	m_parentScene->update();
}

void FigureHandler::continueDrawingCircle(QPointF coordinate)
{
	m_currentCircle->act(ContinueDrawing{coordinate});
	m_parentScene->update();
}

void FigureHandler::continueDrawingTriangle(QPointF coordinate)
{
	if (m_currentTriangle == nullptr)
	{
		return;
	}

	m_currentTriangle->act(ContinueDrawing{coordinate});
	m_parentScene->update();
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
