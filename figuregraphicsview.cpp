#include "figuregraphicsview.h"

FigureGraphicsView::FigureGraphicsView(QGraphicsScene* scene, QWidget* parent)
	: QGraphicsView{scene, parent}
{
	// Проведем основную настройку объекта:
	setupFigureGraphicsView();
}

FigureGraphicsView::~FigureGraphicsView()
{
}

void FigureGraphicsView::setupFigureGraphicsView()
{
	// Включаем постоянный трекинг мыщи на сцене:
	setMouseTracking(true);

	// Задаем основные флаги:
	setRenderHint(QPainter::Antialiasing, true);
	setRenderHint(QPainter::HighQualityAntialiasing, true);
	setRenderHint(QPainter::TextAntialiasing, true);
	setRenderHint(QPainter::SmoothPixmapTransform, true);

	// Задаем основные режимы работы Вью:
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}
