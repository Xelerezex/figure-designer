#ifndef CIRCLE_H
#define CIRCLE_H

#include "figurebase.h"

/*!
 * \brief Класс представления фигуры Окружности
 */
class Circle : public FigureBase
{
	Q_DISABLE_COPY_MOVE(Circle);

public:
	/*!
	 * \brief Основной конструктор
	 * \param fileMenu - указатель на основное Меню
	 * \param parent - указаетль на родительский класс
	 */
	explicit Circle(QMenu* fileMenu, QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~Circle() override;

	/*!
	 * \brief Возвращает тип фигуры
	 * \return тип фигуры
	 */
	[[nodiscard]] int type() const override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие начала отрисовки
	 *        Окружности (visitor)
	 * \param startDrawing - класс действия начала отрисовки Окружности
	 */
	void act(StartDrawing&& startDrawing) override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие продолжения
	 *        отрисовки Окружности (visitor)
	 * \param startDrawing - класс действия продолжения отрисовки Окружности
	 */
	void act(ContinueDrawing&& continueDrawing) override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие продолжения
	 *        отрисовки Окружности (visitor)
	 * \param startDrawing - класс действия продолжения отрисовки Окружности
	 */
	void act(CompleteDrawing&& completeDrawing) override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить сериализацию (visitor)
	 * \param serialize - класс действия сериализации в JSON формат
	 */
	void act (SerializeToJson&& serialize) override;

	/*!
	 * \brief Получить координаты второй точки
	 * \return координаты
	 */
	[[nodiscard]] const QPointF& destination() const;

	/*!
	 * \brief Установить координаты второй точки фигуры
	 * \param newCenter - новые координаты второй точки
	 */
	void setDestination(const QPointF& newDestination);

	/*!
	 * \brief Функция определяет границы фигуры
	 * \return
	 */
	[[nodiscard]] QRectF boundingRect() const override;

	/*!
	 * \brief Функция занимается отрисовкой фигуры
	 * \param painter - указатель на отрисовщик для Фигуры
	 * \param option - указатель на стиль для Фигуры
	 * \param widget - опционально, указатель на виджет, где должна происходить
	 *                 отрисовка
	 */
	void paint(QPainter*					   painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget*						   widget) override;

	/*!
	 * \brief Метод переопределяющий форму Фигуры
	 * \return операции на отрисовку
	 */
	[[nodiscard]] QPainterPath shape() const override;

private:
	/*!
	 * \brief Метод высчитывает границы данного Квадрата относительно центра
	 *        и второй точки
	 * \return границы квадрата
	 */
	[[nodiscard]] QRectF countFigure() const override;

private:
	/*!
	 * \brief Координаты второй Точки, нужной для построения Фигуры
	 */
	QPointF m_destination;
};

#endif // CIRCLE_H
