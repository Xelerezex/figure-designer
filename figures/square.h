#ifndef SQUARE_H
#define SQUARE_H

#include "figurebase.h"

/*!
 * \brief Базовый класс представления квадрата
 */
class Square : public FigureBase
{
	Q_DISABLE_COPY_MOVE(Square);

public:
	/*!
	 * \brief Основной конструктор
	 * \param parent - указаетль на родительский класс
	 */
	explicit Square(QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~Square() override;

	/*!
	 * \brief Возвращает тип фигуры
	 * \return тип фигуры
	 */
	[[nodiscard]] int type() const override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие начала отрисовки
	 *        квадрата (visitor)
	 * \param startDrawing - класс действия начала отрисовки квадрата
	 */
	void act(StartDrawing&& startDrawing) override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие продолжения
	 *        отрисовки квадрата (visitor)
	 * \param startDrawing - класс действия продолжения отрисовки квадрата
	 */
	void act(ContinueDrawing&& continueDrawing) override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие завершения
	 *        отрисовки квадрата (visitor)
	 * \param startDrawing - класс действия завершения отрисовки квадрата
	 */
	void act(CompleteDrawing&& completeDrawing) override;

	/*!
	 * \brief Получить координаты второй точки
	 * \return координаты
	 */
	[[nodiscard]] QPointF destination() const;

	/*!
	 * \brief Установить координаты второй точки фигуры
	 * \param newCenter - новые координаты второй точки
	 */
	void setDestination(QPointF newDestination);

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

#endif // SQUARE_H
