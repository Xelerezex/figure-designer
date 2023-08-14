#include "figuregraphicsview.h"

#include "figurehandler.h"

#include <QMouseEvent>
// DEBUG:
#include <QDebug>

FigureGraphicsView::FigureGraphicsView(QGraphicsScene* scene, QWidget* parent)
	: QGraphicsView{scene, parent}
	, m_currentMode{Mode::Modification}
	, m_figureHandler{new FigureHandler{this}}
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

	// Устанавливаем имя объекта класса
	setObjectName(QLatin1String("FigureGraphicsView"));
}

FigureGraphicsView::Mode FigureGraphicsView::currentMode() const
{
	// DEBUG:
	qDebug() << m_currentMode;
	return m_currentMode;
}

bool FigureGraphicsView::isTriangleMode() const
{
	return m_currentMode == TriangleDraw;
}

void FigureGraphicsView::setCurrentMode(Mode newCurrentMode)
{
	m_currentMode = newCurrentMode;
}

void FigureGraphicsView::mousePressEvent(QMouseEvent* mouseEvent)
{
	if (mouseEvent->button() == Qt::LeftButton)
	{
		onMouseLeftButtonPressed(mouseEvent);
	}
}

void FigureGraphicsView::mouseMoveEvent(QMouseEvent* mouseEvent)
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

void FigureGraphicsView::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
	if (mouseEvent->button() == Qt::LeftButton)
	{
		onMouseLeftButtonReleased(mouseEvent);
	}
}

void FigureGraphicsView::onMouseLeftButtonPressed(QMouseEvent* mouseEvent)
{
	// Запоминаем место, где произошло нажатие
	m_figureHandler->setLastLeftMousePressed(mapToScene(mouseEvent->pos()));

	if (m_currentMode == SquareDraw)
	{
		m_figureHandler->addNewSquare(mapToScene(mouseEvent->pos()));
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_figureHandler->addNewRectangle(mapToScene(mouseEvent->pos()));
	}
	else if (m_currentMode == CircleDraw)
	{
		m_figureHandler->addNewCircle(mapToScene(mouseEvent->pos()));
	}
	else if (m_currentMode == TriangleDraw)
	{
	}

	qDebug("mousePressEvent");

	// Вызов метода базового класса
	QGraphicsView::mousePressEvent(mouseEvent);
}

void FigureGraphicsView::onMouseLeftButtonMoved(QMouseEvent* mouseEvent)
{
	if (m_currentMode == SquareDraw)
	{
		m_figureHandler->continueDrawingSquare(mapToScene(mouseEvent->pos()));
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_figureHandler->continueDrawingRectangle(
			mapToScene(mouseEvent->pos()));
	}
	else if (m_currentMode == CircleDraw)
	{
		m_figureHandler->continueDrawingCircle(mapToScene(mouseEvent->pos()));
	}
	else if (m_currentMode == Modification)
	{
		// TODO: Сделать обновление координат фигуры, в режиме передвижения
		// Вызов метода базового класса
		QGraphicsView::mouseMoveEvent(mouseEvent);
	}

	qDebug("mouseMoveEvent");
}

void FigureGraphicsView::onMouseLeftButtonReleased(QMouseEvent* mouseEvent)
{
	if (m_currentMode == SquareDraw)
	{
		m_figureHandler->completeSquare(mapToScene(mouseEvent->pos()));
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_figureHandler->completeRectangle(mapToScene(mouseEvent->pos()));
	}
	else if (m_currentMode == CircleDraw)
	{
		m_figureHandler->completeCircle(mapToScene(mouseEvent->pos()));
	}
	else if (m_currentMode == TriangleDraw)
	{
		m_figureHandler->addNewTriangleDot(mapToScene(mouseEvent->pos()));
	}

	qDebug("mouseReleaseEvent");

	// Вызов метода базового класса
	QGraphicsView::mouseReleaseEvent(mouseEvent);
}

void FigureGraphicsView::onEmptyMouseMoved(QMouseEvent* mouseEvent)
{
	if (m_currentMode == TriangleDraw)
	{
		m_figureHandler->continueDrawingTriangle(mapToScene(mouseEvent->pos()));
	}
}
