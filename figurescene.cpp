#include "figurescene.h"

#include <QMenu>
// DEBUG:
#include <QDebug>

FigureScene::FigureScene(/*QMenu* itemMenu, */ QObject* parent)
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
	// DEBUG:
	qDebug() << m_currentMode;
	return m_currentMode;
}

void FigureScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode == Modification)
	{
		QGraphicsScene::mousePressEvent(mouseEvent);
	}
}

void FigureScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode == Modification)
	{
		qDebug() << "emitted";
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
}

void FigureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (m_currentMode == Modification)
	{
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
