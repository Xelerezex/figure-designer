#ifndef FIGUREGRAPHICSVIEW_H
#define FIGUREGRAPHICSVIEW_H

#include <QGraphicsView>

QT_BEGIN_NAMESPACE
class FigureHandler;
QT_END_NAMESPACE

/*!
 * \brief Класс представления для Сцены
 */
class FigureGraphicsView : public QGraphicsView
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(FigureGraphicsView)

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
	 * \param scene - указатель на сцену
	 * \param parent - указатель на родительский виджет
	 */
	explicit FigureGraphicsView(QGraphicsScene* scene,
								QWidget*		parent = nullptr);

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
	 * \brief Установить текущий режим сцены
	 * \param newCurrentMode - новый режим
	 */
	// TODO: перенести в приват
	void setCurrentMode(Mode newCurrentMode);

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

private:
	/*!
	 * \brief Метод настраивает этот объект Вью
	 */
	void setupFigureGraphicsView();

	void onMouseLeftButtonPressed(QMouseEvent* mouseEvent);
	void onMouseLeftButtonMoved(QMouseEvent* mouseEvent);
	void onMouseLeftButtonReleased(QMouseEvent* mouseEvent);
	void onEmptyMouseMoved(QMouseEvent* mouseEvent);

private:
	/*!
	 * \brief Режим работы в котором, в данный момент времени, находится сцена
	 */
	Mode m_currentMode;

	/*!
	 * \brief Указатель на обработчик взаимодействий с Фигурами
	 */
	FigureHandler* m_figureHandler;
};

#endif // FIGUREGRAPHICSVIEW_H
