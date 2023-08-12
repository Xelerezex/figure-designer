#ifndef SQUARE_H
#define SQUARE_H

#include "figurebase.h"

class Square : public FigureBase
{
public:
	/*!
	 * \brief Основной конструктор
	 * \param parent - указаетль на родительский класс
	 */
	Square(QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~Square();

	/*!
	 * \brief Получить координаты точки центра
	 * \return координаты
	 */
	QPointF center() const;

	/*!
	 * \brief Установить координаты центра фигуры
	 * \param newCenter - новые координаты центра
	 */
	void setCenter(QPointF newCenter);

	/*!
	 * \brief Получить координаты второй точки
	 * \return координаты
	 */
	QPointF destination() const;

	/*!
	 * \brief Установить координаты второй точки фигуры
	 * \param newCenter - новые координаты второй точки
	 */
	void setDestination(QPointF newDestination);

	/*!
	 * \brief Функция определяет границы фигуры
	 * \return
	 */
	QRectF boundingRect() const override;

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
	QRectF countFigure() const override;

private:
	/*!
	 * \brief Координаты центра фигуры
	 */
	QPointF m_center;

	/*!
	 * \brief Координаты второй Точки, нужной для построения Фигуры
	 */
	QPointF m_destination;
};

#endif // SQUARE_H
