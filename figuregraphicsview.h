#ifndef FIGUREGRAPHICSVIEW_H
#define FIGUREGRAPHICSVIEW_H

#include <QGraphicsView>

QT_BEGIN_NAMESPACE
class QMenu;
class ClickTracker;
class FigureHandler;
class CentralWidget;
QT_END_NAMESPACE

/*!
 * \brief Класс представления для Сцены
 */
class FigureGraphicsView : public QGraphicsView
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(FigureGraphicsView)

	// Разрешает центральному виджету изменять режим работы графической сцены
	friend CentralWidget;

public:
	/*!
	 * \brief Основные режимы работы графической сцены
	 */
	enum Mode
	{
		Modification, /*!< Режим Модификации */
		SquareDraw,	  /*!< Режим отрисовки Квадрата */
		RectangleDraw, /*!< Режим отрисовки Прямоугольника */
		TriangleDraw, /*!< Режим отрисовки Треугольника */
		CircleDraw /*!< Режим отрисовки Круга */
	};
	Q_ENUM(Mode);

	/*!
	 * \brief Дефолтный удаленный конструктор
	 */
	FigureGraphicsView() = delete;

	/*!
	 * \brief Основной конструктор
	 * \param fileMenu - указатель на основное Меню
	 * \param scene - указатель на сцену
	 * \param parent - указатель на родительский виджет
	 */
	explicit FigureGraphicsView(QMenu*			fileMenu,
								QGraphicsScene* scene,
								QWidget*		parent);

	/*!
	 * \brief Основной деструктор
	 */
	~FigureGraphicsView() override;

	/*!
	 * \brief Вернуть режим, в котором сейчас находится сцена
	 * \return режим сцены
	 */
	[[nodiscard]] Mode currentMode() const;

	/*!
	 * \brief Проверка признака нахождения сцены в режиме отрисовки треугольника
	 * \return true - если сцена находится в режиме отрисовки треугольника
	 */
	[[nodiscard]] bool isTriangleMode() const;

	/*!
	 * \brief Вернуть все данные со сцены
	 * \return мап c данными
	 */
	[[nodiscard]] QJsonDocument figuresData();

	/*!
	 * \brief Загрузить данные в сцену из QJsonDocument
	 * \param document - документ с закгружденными данными
	 */
	void addedLoadedData(QJsonDocument& document);

protected:
	/*!
	 * \brief Переопределнный метод Нажатия Кнопки Мыщи
	 * \param mouseEvent - указатель на событие
	 */
	void mousePressEvent(QMouseEvent* mouseEvent) override;

	/*!
	 * \brief Переопределнный метод Движения Мыщи
	 * \param mouseEvent - указатель на событие
	 */
	void mouseMoveEvent(QMouseEvent* mouseEvent) override;

	/*!
	 * \brief Переопределнный метод Отжатия Кнопки Мыщи
	 * \param mouseEvent - указатель на событие
	 */
	void mouseReleaseEvent(QMouseEvent* mouseEvent) override;

	/*!
	 * \brief Переопределнный метод двойного клика Кнопки Мыщи
	 * \param mouseEvent - указатель на событие
	 */
	void mouseDoubleClickEvent(QMouseEvent* mouseEvent) override;

private:
	/*!
	 * \brief Установить текущий режим сцены
	 * \param newCurrentMode - новый режим
	 */
	void setCurrentMode(Mode newCurrentMode);

	/*!
	 * \brief Метод настраивает этот объект Вью
	 */
	void setupFigureGraphicsView();

	/*!
	 * \brief Метод, вызываемый при нажатии на левую кнопку мыщи
	 * \param mouseEvent - событие мыщи
	 */
	void onMouseLeftButtonPressed(QMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при движении с зажатой кнопкой мыщи
	 * \param mouseEvent - событие мыщи
	 */
	void onMouseLeftButtonMoved(QMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при разжатии левой кнопки мыщи
	 * \param mouseEvent - событие мыщи
	 */
	void onMouseLeftButtonReleased(QMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при движении мыщи
	 * \param mouseEvent - событие мыщи
	 */
	void onEmptyMouseMoved(QMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при нажатии на правую кнопку мыщи
	 * \param mouseEvent - событие мыщи
	 */
	void onMouseRightButtonPressed(QMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при движении с зажатой правой кнопкой мыщи
	 * \param mouseEvent - событие мыщи
	 */
	void onMouseRightButtonMoved(QMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при разжатии правой кнопки мыщи
	 * \param mouseEvent - событие мыщи
	 */
	void onMouseRightButtonReleased(QMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при нажатии на среднюю кнопку мыщи
	 * \param mouseEvent - событие мыщи
	 */
	void onMouseMiddleButtonPressed(QMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при движении с зажатой средней кнопкой мыщи
	 * \param mouseEvent - событие мыщи
	 */
	void onMouseMiddleButtonMoved(QMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при отжиме средней кнопкой мыщи
	 * \param mouseEvent - событие мыщи
	 */
	void onMouseMiddleButtonReleased(QMouseEvent* mouseEvent);

	/*!
	 * \brief Метод проверяет, есть ли по данным координатам какой-то объект
	 * \param sceneCoord - координаты сцены
	 * \return true - если сцена не пуста и объект есть
	 */
	[[nodiscard]] bool isOnSelectedFigure(const QPointF& sceneCoord) const;

	/*!
	 * \brief Метод для дебага
	 * \param mouseEvent
	 */
	void printEventInfo(QMouseEvent* mouseEvent) const;

private:
	/*!
	 * \brief Режим работы в котором, в данный момент времени, находится сцена
	 */
	Mode m_currentMode;

	/*!
	 * \brief Указатель на Меню Файл
	 */
	QMenu* m_pFileMenu;

	/*!
	 * \brief Указатель на класс трекающий клики кнопок
	 */
	ClickTracker* m_clickTracker;

	/*!
	 * \brief Указатель на обработчик взаимодействий с Фигурами
	 */
	FigureHandler* m_figureHandler;
};

#endif // FIGUREGRAPHICSVIEW_H
