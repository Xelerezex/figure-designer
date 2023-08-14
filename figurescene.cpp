#include "figurescene.h"

#include <QMenu>

FigureScene::FigureScene(/*QMenu* itemMenu, */ QObject* parent)
	: QGraphicsScene{parent}
{
	// Настраиваем сцену
	setupFigureScene();
}

FigureScene::~FigureScene()
{
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
