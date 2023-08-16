#ifndef FIGUREBASE_H
#define FIGUREBASE_H

#include <QGraphicsItem>

class StartDrawing;
class ContinueDrawing;
class CompleteDrawing;

/*!
 * \brief Базовый класс представления фигуры
 */
class FigureBase : public QGraphicsItem
{
	Q_DISABLE_COPY_MOVE(FigureBase);

public:
	/*!
	 *  \brief Типы графических элементов
	 */
	enum
	{
		Square	  = UserType + 1, /*! Квадрат <*/
		Rectangle = UserType + 2, /*! Прямоугольник <*/
		Triangle  = UserType + 3, /*! Треугольник <*/
		Circle	  = UserType + 4, /*! Окружность <*/
		SelectionRectangle = UserType + 5, /*! Прямоугольник выделения <*/
	};

	/*!
	 * \brief Удаленный дефолтный конструктор
	 */
	FigureBase() = delete;

	/*!
	 * \brief Дефолтный деструктор
	 */
	~FigureBase() override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие начала отрисовки
	 *        фигуры (visitor)
	 * \param startDrawing - класс действия начала отрисовки фигуры
	 */
	virtual void act(StartDrawing&& startDrawing) = 0;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие продолжения
	 *        отрисовки фигуры (visitor)
	 * \param startDrawing - класс действия продолжения отрисовки фигуры
	 */
	virtual void act(ContinueDrawing&& continueDrawing) = 0;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие завершения
	 *        отрисовки фигуры (visitor)
	 * \param startDrawing - класс действия завершения отрисовки фигуры
	 */
	virtual void act(CompleteDrawing&& completeDrawing) = 0;

	/*!
	 * \brief Получить координаты точки центра
	 * \return координаты
	 */
	[[nodiscard]] const QPointF& center() const;

	/*!
	 * \brief Установить координаты центра фигуры
	 * \param newCenter - новые координаты центра
	 */
	void setCenter(const QPointF& newCenter);

	/*!
	 * \brief Метод должен вызываться когда начинается первичное создание
	 *        объекта и его первичная отрисовка.
	 */
	void startCreating();

	/*!
	 * \brief Метод должен быть вызван при завершении создания и первичной
	 *        настрйоки объекта
	 */
	void completeCreating();

	/*!
	 * \brief Метод возвращает признак отсутсвия объекта на сцене
	 * \return true - метод отсутсвует
	 */
	[[nodiscard]] bool isNotExisting() const;

	/*!
	 * \brief Метод возвращает признак полного создания элемента
	 * \return true - если создание завершено
	 */
	[[nodiscard]] bool isFullyCreated() const;

protected:
	/*!
	 * \brief Основной конструктор
	 * \param parent - указатель на родительский класс
	 */
	explicit FigureBase(QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Метод высчитывает границы данного Квадрата относительно центра
	 *        и второй точки
	 * \return границы квадрата
	 */
	[[nodiscard]] virtual QRectF countFigure() const = 0;

private:
	/*!
	 * \brief Жизненый цикл объекта Сцены
	 */
	enum LifeCycle
	{
		NotExisting,
		Creating,
		FullyCreated
	};

	/*!
	 * \brief Текущий жизненый цикл
	 */
	LifeCycle m_currentCycle;

	/*!
	 * \brief Координаты центра фигуры
	 */
	QPointF m_center;
};

#endif // FIGUREBASE_H
