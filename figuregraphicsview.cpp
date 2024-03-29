#include "figuregraphicsview.h"

#include "clicktracker.h"
#include "figurehandler.h"

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGuiApplication>
#include <QMenu>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "figures/figurebase.h"

FigureGraphicsView::FigureGraphicsView(QMenu*		   fileMenu,
									   QGraphicsScene* scene,
									   QWidget*		   parent)
	: QGraphicsView{scene, parent}
	, m_currentMode{Mode::Modification}
	, m_pFileMenu{fileMenu}
	, m_clickTracker{new ClickTracker{this}}
	, m_figureHandler{new FigureHandler{m_pFileMenu, m_clickTracker, this}}
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

	// Данные флаги делают HD рендеринг
	// setRenderHint(QPainter::Antialiasing, true);
	// setRenderHint(QPainter::HighQualityAntialiasing, true);
	// setRenderHint(QPainter::SmoothPixmapTransform, true);

	// Задаем основные флаги:
	setRenderHint(QPainter::Antialiasing, false);
	setDragMode(QGraphicsView::NoDrag);
	setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	// Включаем кеширование бекграунда
	setCacheMode(QGraphicsView::CacheBackground);

	// Задаем основные режимы работы Вью:
	setViewportUpdateMode(QGraphicsView::QGraphicsView::FullViewportUpdate);

	// Устанавливаем имя объекта класса
	setObjectName(QLatin1String("FigureGraphicsView"));
}

FigureGraphicsView::Mode FigureGraphicsView::currentMode() const
{
	return m_currentMode;
}

bool FigureGraphicsView::isTriangleMode() const
{
	return m_currentMode == TriangleDraw;
}

QJsonDocument FigureGraphicsView::figuresData()
{
	QJsonArray recordsArray;
	foreach (const auto& item, items())
	{
		recordsArray.push_back(m_figureHandler->serializeFigure(item));
	}

	QJsonDocument doc{recordsArray};
	return doc;
}

void FigureGraphicsView::addedLoadedData(QJsonDocument& document)
{
	foreach (const QJsonValue& item, document.array())
	{
		QJsonObject object{item.toObject()};
		m_figureHandler->deserializeFigure(object);
	}
}

void FigureGraphicsView::mousePressEvent(QMouseEvent* mouseEvent)
{
	// Нажата ли Левая кнопка мыщи
	const bool isLeftButtonPressed{mouseEvent->button() == Qt::LeftButton};
	// Нажата ли Правая кнопка мыщи
	const bool isRightButtonPressed{mouseEvent->button() == Qt::RightButton};
	// Нажата ли Средняя кнопка мыщи
	const bool isMiddleButtonPressed{mouseEvent->button() == Qt::MiddleButton};

	if (isLeftButtonPressed)
	{
		onMouseLeftButtonPressed(mouseEvent);
	}
	else if (isRightButtonPressed)
	{
		onMouseRightButtonPressed(mouseEvent);
	}
	else if (isMiddleButtonPressed)
	{
		onMouseMiddleButtonPressed(mouseEvent);
	}
}

void FigureGraphicsView::mouseMoveEvent(QMouseEvent* mouseEvent)
{
	// true - только если движение с зажатой левой кнопокой мыщи
	bool onlyWithLeftButtonMove{
		static_cast<bool>(mouseEvent->buttons() & Qt::LeftButton)};
	// true - только если движение с зажатой правой кнопокой мыщи
	bool onlyWithRightButtonMove{
		static_cast<bool>(mouseEvent->buttons() & Qt::RightButton)};
	// true - только если движение с зажатой правой кнопокой мыщи
	bool onlyWithMiddleButtonMove{
		static_cast<bool>(mouseEvent->buttons() & Qt::MiddleButton)};

	// true - если движение мыщи без зажатых кнопок
	bool onlyMouseMove{mouseEvent->buttons() == Qt::NoButton};

	if (onlyWithLeftButtonMove)
	{
		onMouseLeftButtonMoved(mouseEvent);
	}
	else if (onlyWithRightButtonMove)
	{
		onMouseRightButtonMoved(mouseEvent);
	}
	else if (onlyWithMiddleButtonMove)
	{
		onMouseMiddleButtonMoved(mouseEvent);
	}

	if (onlyMouseMove && isTriangleMode())
	{
		onEmptyMouseMoved(mouseEvent);
	}
}

void FigureGraphicsView::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
	// Отжата ли Левая кнопка мыщи
	const bool isLeftButtonReleased{mouseEvent->button() == Qt::LeftButton};
	// true - только если отжата правая кнопокой мыщи
	bool isRightButtonReleased{mouseEvent->button() == Qt::RightButton};
	// true - только если отжата центральная кнопка мыщи
	bool isMiddleButtonReleased{mouseEvent->button() == Qt::MiddleButton};

	if (isLeftButtonReleased)
	{
		onMouseLeftButtonReleased(mouseEvent);
	}
	else if (isRightButtonReleased)
	{
		onMouseRightButtonReleased(mouseEvent);
	}
	else if (isMiddleButtonReleased)
	{
		onMouseMiddleButtonReleased(mouseEvent);
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
		m_figureHandler->continueDrawingRectangle(itemCoord);
	}
	else if (m_currentMode == CircleDraw)
	{
		m_figureHandler->continueDrawingCircle(itemCoord);
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

void FigureGraphicsView::onMouseRightButtonPressed(QMouseEvent* mouseEvent)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	// Координаты фигуры в системе кординат Элемента Сцены
	const auto itemCoord = mouseEvent->pos();
	// Координаты фигуры на Сцене
	const auto sceneCoord = mapToScene(itemCoord);

	if (isOnSelectedFigure(sceneCoord))
	{
		// Прокидываем нажатие Правой кнопки на сцену
		QGraphicsView::mousePressEvent(mouseEvent);
	}
}

void FigureGraphicsView::onMouseRightButtonMoved(QMouseEvent* mouseEvent)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	// Координаты фигуры в системе кординат Элемента Сцены
	const auto itemCoord = mouseEvent->pos();
	// Координаты фигуры на Сцене
	const auto sceneCoord = mapToScene(itemCoord);

	if (isOnSelectedFigure(sceneCoord))
	{
		// Прокидываем зажатие + движение Правой кнопки на сцену
		QGraphicsView::mouseMoveEvent(mouseEvent);
	}
}

void FigureGraphicsView::onMouseRightButtonReleased(QMouseEvent* mouseEvent)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	// Координаты фигуры в системе кординат Элемента Сцены
	const auto itemCoord = mouseEvent->pos();
	// Координаты фигуры на Сцене
	const auto sceneCoord = mapToScene(itemCoord);

	// if (isOnSelectedFigure(sceneCoord))
	//{
	//  Прокидываем отжатие Правой кнопки на сцену
	QGraphicsView::mouseReleaseEvent(mouseEvent);
	//}
}

void FigureGraphicsView::onMouseMiddleButtonPressed(QMouseEvent* mouseEvent)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	// Координаты фигуры в системе кординат Элемента Сцены
	const auto itemCoord = mouseEvent->pos();
	// Координаты фигуры на Сцене
	const auto sceneCoord = mapToScene(itemCoord);

	if (isOnSelectedFigure(sceneCoord))
	{
		// Клонируем все выделенные объекты:
		m_figureHandler->cloneSelectedItems();

		// Прокидываем нажатие на левую кнопку мыщи
		QMouseEvent fakeEvent{QEvent::MouseButtonPress,
							  mouseEvent->localPos(),
							  mouseEvent->screenPos(),
							  Qt::LeftButton,
							  Qt::LeftButton,
							  mouseEvent->modifiers()};
		QGraphicsView::mousePressEvent(&fakeEvent);
	}
}

void FigureGraphicsView::onMouseMiddleButtonMoved(QMouseEvent* mouseEvent)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	QMouseEvent fakeEvent{QEvent::MouseMove,
						  mouseEvent->localPos(),
						  mouseEvent->screenPos(),
						  Qt::LeftButton,
						  Qt::LeftButton,
						  mouseEvent->modifiers()};

	QGraphicsView::mouseMoveEvent(&fakeEvent);
}

void FigureGraphicsView::onMouseMiddleButtonReleased(QMouseEvent* mouseEvent)
{
	if (m_currentMode != Modification)
	{
		return;
	}

	// Координаты фигуры в системе кординат Элемента Сцены
	const auto itemCoord = mouseEvent->pos();
	// Координаты фигуры на Сцене
	const auto sceneCoord = mapToScene(itemCoord);

	if (isOnSelectedFigure(sceneCoord))
	{
		QMouseEvent fakeEvent{QEvent::MouseButtonRelease,
							  mouseEvent->localPos(),
							  mouseEvent->screenPos(),
							  Qt::LeftButton,
							  Qt::LeftButton,
							  mouseEvent->modifiers()};
		QGraphicsView::mouseReleaseEvent(&fakeEvent);
	}
	QGraphicsView::mouseReleaseEvent(mouseEvent);
}

bool FigureGraphicsView::isOnSelectedFigure(const QPointF& sceneCoord) const
{
	// Указатель на фигуру
	QGraphicsItem* figure = scene()->itemAt(sceneCoord, QTransform{});

	return figure != nullptr && figure->isSelected();
}

// #include <QDebug>
void FigureGraphicsView::printEventInfo(QMouseEvent* mouseEvent) const
{
	// 	qDebug() << " TYPE      : " << mouseEvent->type() << "\n"
	// 			 << "LOCAL POS :" << mouseEvent->localPos() << "\n"
	// 			 << "SCREEN POS:" << mouseEvent->screenPos() << "\n"
	// 			 << "BUTTON    :" << mouseEvent->button() << "\n"
	// 			 << "BUTTONS   :" << mouseEvent->buttons() << "\n"
	// 			 << "MODIFIERS :" << mouseEvent->modifiers() << "\n";
}
