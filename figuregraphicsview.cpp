#include "figuregraphicsview.h"

#include "figurehandler.h"
#include "modificationhandler.h"

#include <QMouseEvent>

// DEBUG:
#include <QDebug>

FigureGraphicsView::FigureGraphicsView(QGraphicsScene* scene, QWidget* parent)
	: QGraphicsView{scene, parent}
	, m_currentMode{Mode::Modification}
	, m_figureHandler{new FigureHandler{this}}
	, m_moificationHandler{new ModificationHandler{this}}
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

	// Была ли нажата кнопка над фигурой
	const bool clickedOnFigure{itemAt(mouseEvent->pos()) != nullptr};

	// Запоминаем место, где произошло нажатие
	m_figureHandler->setLastLeftMousePressed(sceneCoord);

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
		// TODO: Сделать m_modificationHandler

		// DEBUG:
		qDebug() << "Modification pressed left"
				 << "On figure" << clickedOnFigure;
		if (clickedOnFigure)
		{
			// Вызов метода базового класса
			QGraphicsView::mousePressEvent(mouseEvent);
		}
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
		// DEBUG:
		qDebug() << "Modification moved with left";

		// Вызов метода базового класса
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
		m_figureHandler->isLeftMouseClicked(sceneCoord)};

	// Запоминаем место, где произошло отжатие
	m_figureHandler->setLastLeftMouseReleased(sceneCoord);

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
		// Координаты фигуры на Сцене
		const auto sceneCoord = mapToScene(itemCoord);
		m_figureHandler->addNewTriangleDot(itemCoord, sceneCoord);
	}
	else if (isModificationMode)
	{
		// DEBUG:
		qDebug() << "Modification released"
				 << "isMode" << isModificationMode << "isClicked"
				 << isLeftMouseClicked;

		if (isLeftMouseClicked)
		{
			// Вызов метода базового класса
			QGraphicsView::mouseReleaseEvent(mouseEvent);
		}
	}
}

void FigureGraphicsView::onEmptyMouseMoved(QMouseEvent* mouseEvent)
{
	if (m_currentMode == TriangleDraw)
	{
		m_figureHandler->continueDrawingTriangle(mouseEvent->pos());
	}
}
