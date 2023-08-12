#include "figurescene.h"

#include <QMenu>

// DEBUG:
#include <QDebug>

FigureScene::FigureScene(QMenu* itemMenu, QObject* parent)
	: QGraphicsScene{parent}
	, m_currentMode{Mode::Modification}
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

void FigureScene::setCurrentMode(Mode newCurrentMode)
{
	// DEBUG:
	qDebug() << newCurrentMode;

	m_currentMode = newCurrentMode;
}

void FigureScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode == SquareDraw)
	{
	}

	// Вызов метода базового класса
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode == SquareDraw)
	{
	}

	// Вызов метода базового класса
	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode == SquareDraw)
	{
	}

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
