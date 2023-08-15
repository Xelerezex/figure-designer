#include "figuregraphicsview.h"

#include "clicktracker.h"
#include "figurehandler.h"

#include <QMouseEvent>
#include <QGuiApplication>

// DEBUG:
#include <QDebug>

FigureGraphicsView::FigureGraphicsView(QGraphicsScene* scene, QWidget* parent)
	: QGraphicsView{scene, parent}
	, m_currentMode{Mode::Modification}
	, m_clickTracker{new ClickTracker{this}}
	, m_figureHandler{new FigureHandler{this, m_clickTracker}}
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

void FigureGraphicsView::mousePressEvent(QMouseEvent* mouseEvent)
{
	// Нажата ли Левая кнопка мыщи
	const bool isLeftButton{mouseEvent->button() == Qt::LeftButton};

	if (isLeftButton)
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
	// Нажата ли Левая кнопка мыщи
	const bool isLeftButton{mouseEvent->button() == Qt::LeftButton};

	if (isLeftButton)
	{
		onMouseLeftButtonReleased(mouseEvent);
	}
}

void FigureGraphicsView::mouseDoubleClickEvent(QMouseEvent* mouseEvent)
{
	// Блокируем все эвенты с двойным нажатием Мыщи по все йерархии
	Q_UNUSED(mouseEvent);
}

void FigureGraphicsView::setCurrentMode(Mode newCurrentMode)
{
	m_currentMode = newCurrentMode;
}

void FigureGraphicsView::onMouseLeftButtonPressed(QMouseEvent* mouseEvent)
{
	// Координаты фигуры в системе кординат Элемента Сцены
	const auto itemCoord = mouseEvent->pos();
	// Координаты фигуры на Сцене
	const auto sceneCoord = mapToScene(itemCoord);

	// Запоминаем место, где произошло нажатие
	m_clickTracker->setLastLeftMousePressed(sceneCoord);

	if (m_currentMode == SquareDraw)
	{
		m_figureHandler->addNewSquare(itemCoord, sceneCoord);
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_figureHandler->addNewRectangle(itemCoord, sceneCoord);
	}
	else if (m_currentMode == CircleDraw)
	{
		m_figureHandler->addNewCircle(itemCoord, sceneCoord);
	}
	else if (m_currentMode == Modification)
	{
		QGraphicsView::mousePressEvent(mouseEvent);
	}
}

void FigureGraphicsView::onMouseLeftButtonMoved(QMouseEvent* mouseEvent)
{
	// Координаты фигуры в системе кординат Элемента Сцены
	const auto itemCoord = mouseEvent->pos();

	if (m_currentMode == SquareDraw)
	{
		m_figureHandler->continueDrawingSquare(itemCoord);
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_figureHandler->continueDrawingRectangle(mouseEvent->pos());
	}
	else if (m_currentMode == CircleDraw)
	{
		m_figureHandler->continueDrawingCircle(mouseEvent->pos());
	}
	else if (m_currentMode == Modification)
	{
		QGraphicsView::mouseMoveEvent(mouseEvent);
	}
}

void FigureGraphicsView::onMouseLeftButtonReleased(QMouseEvent* mouseEvent)
{
	// Координаты фигуры в системе кординат Элемента Сцены
	const auto itemCoord = mouseEvent->pos();
	// Координаты фигуры на Сцене
	const auto sceneCoord = mapToScene(itemCoord);

	// Проверка на режим модификации
	const bool isModificationMode{m_currentMode == Modification};
	// Проверка на то, произошел ли клик
	const bool isLeftMouseClicked{
		m_clickTracker->isLeftMouseClicked(sceneCoord)};

	// Запоминаем место, где произошло отжатие
	m_clickTracker->setLastLeftMouseReleased(sceneCoord);

	// Проверим произошел ли клик
	if (!isModificationMode && isLeftMouseClicked)
	{
		m_figureHandler->abortDrawing();
	}

	if (m_currentMode == SquareDraw)
	{
		m_figureHandler->completeSquare(itemCoord);
	}
	else if (m_currentMode == RectangleDraw)
	{
		m_figureHandler->completeRectangle(itemCoord);
	}
	else if (m_currentMode == CircleDraw)
	{
		m_figureHandler->completeCircle(itemCoord);
	}
	else if (m_currentMode == TriangleDraw)
	{
		m_figureHandler->addNewTriangleDot(itemCoord, sceneCoord);
	}
	else if (m_currentMode == Modification)
	{
		QGraphicsView::mouseReleaseEvent(mouseEvent);
	}
}

void FigureGraphicsView::onEmptyMouseMoved(QMouseEvent* mouseEvent)
{
	if (m_currentMode == TriangleDraw)
	{
		m_figureHandler->continueDrawingTriangle(mouseEvent->pos());
	}
}
