#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figurebase.h"

class Triangle : public FigureBase
{
public:
	/*!
	 * \brief Основной конструктор
	 * \param parent - указаетль на родительский класс
	 */
	explicit Triangle(QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~Triangle();

	void act(StartDrawing&& startDrawing) override;
	void act(ContinueDrawing&& continueDrawing) override;
	void act(CompleteDrawing&& completeDrawing) override;
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
	 * \brief Установить координаты первой точки фигуры
	 * \param newCenter - новые координаты первой точки
	 */
	void setFirst(QPointF newFirst);

	/*!
	 * \brief Установить координаты второй точки фигуры
	 * \param newCenter - новые координаты второй точки
	 */
	void setSecond(QPointF newSecond);

	/*!
	 * \brief Установить координаты третьей точки фигуры
	 * \param newCenter - новые координаты третьей точки
	 */
	void setThird(QPointF newThird);

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

	/*!
	 * \brief Метод переопределяющий форму Фигуры
	 * \return операции на отрисовку
	 */
	QPainterPath shape() const override;

private:
	/*!
	 * \brief Метод высчитывает границы данного Квадрата относительно центра
	 *        и второй точки
	 * \return границы квадрата
	 */
	QRectF countFigure() const override;

private:
	enum DrawingStatus
	{
		NotDrawn,
		FirstPointDrawn,
		SecondPointDrawn,
		ThirdPointDrawn,
	};

	/*!
	 * \brief Координаты центра фигуры
	 */
	QPointF m_center;

	/*!
	 * \brief Координаты первой точки
	 */
	QPointF m_first;

	/*!
	 * \brief Координаты второй точки
	 */
	QPointF m_second;

	/*!
	 * \brief Координаты третьей точки
	 */
	QPointF m_third;
};

#endif // TRIANGLE_H
