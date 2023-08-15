#include "figurescene.h"

#include "clicktracker.h"
#include "modificationhandler.h"

#include <QMenu>
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
	const QPointF  sceneCoord = mouseEvent->scenePos();

	QGraphicsItem* figure = itemAt(sceneCoord, QTransform{});

	if (m_currentMode == Modification)
	{
		m_clickTracker->setLastLeftMousePressed(sceneCoord);
		qDebug() << "Pressed at:" << sceneCoord;

		if (figure != nullptr)
		{
			qDebug() << "Item at" << sceneCoord << "is" << figure->type();
			QGraphicsScene::mousePressEvent(mouseEvent);
		}
	}
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	const QPointF sceneCoord = mouseEvent->scenePos();

	if (m_currentMode == Modification)
	{
		qDebug() << "Moved to:" << sceneCoord;
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	const QPointF sceneCoord = mouseEvent->scenePos();

	if (m_currentMode == Modification)
	{
		m_modificationHandler->modificateOnLeftMouseReleased(sceneCoord);
		QGraphicsScene::mouseReleaseEvent(mouseEvent);
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
}

void FigureScene::setCurrentMode(Mode newCurrentMode)
{
	m_currentMode = newCurrentMode;
}
