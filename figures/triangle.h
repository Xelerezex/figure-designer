#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figurebase.h"

class DrawDot;

class Triangle : public FigureBase
{
	// Действия над фигурами дружественные классы:
	friend StartDrawing;
	friend ContinueDrawing;
	friend CompleteDrawing;

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
	 * \brief Метод проверяет установлена ли первая точка Треугольника
	 * \return true - если у первой точки уже есть координата
	 */
	bool isFirstDrawn() const;

	/*!
	 * \brief Установить координаты второй точки фигуры
	 * \param newCenter - новые координаты второй точки
	 */
	void setSecond(QPointF newSecond);

	/*!
	 * \brief Метод проверяет установлена ли вторая точка Треугольника
	 * \return true - если у второй точки уже есть координата
	 */
	bool isSecondDrawn() const;

	/*!
	 * \brief Установить координаты третьей точки фигуры
	 * \param newCenter - новые координаты третьей точки
	 */
	void setThird(QPointF newThird);

	/*!
	 * \brief Метод проверяет установлена ли третья точка Треугольника
	 * \return true - если у третьей точки уже есть координата
	 */
	bool isThirdDrawn() const;

	/*!
	 * \brief При вызыве метода начинается отрисовка линии, идущей за мышкой
	 */
	void startDrawingLine();

	/*!
	 * \brief При вызыве метода заканчивается отрисовка линии, идущей за мышкой
	 */
	void stopDrawingLine();

	/*!
	 * \brief Отрисовывается ли сейчас линия
	 * \return true - если отрисовывается
	 */
	bool isLineDrawing() const;

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
	 * \brief Статус отрисовки треугольника
	 */
	enum DrawingStatus
	{
		NotDrawn, /*!< В треугольнике нет ни одной точки */
		FirstPointDrawn, /*!< В треугольнике обозначена точка один */
		SecondPointDrawn, /*!< В треугольнике обозначена точка два */
		ThirdPointDrawn, /*!< В треугольнике обозначена точка три */
	};

	/*!
	 * \brief Метод высчитывает как будет выглядеть полигон для Треугольника
	 * \return полигон треугольника
	 */
	QPolygonF countPolygon() const;

	/*!
	 * \brief Метод высчитывает границы данного Квадрата относительно центра
	 *        и второй точки
	 * \return границы квадрата
	 */
	QRectF countFigure() const override;

	/*!
	 * \brief Установить статус отрисовки треугольника
	 * \param newStatus - новый статус
	 */
	void setStatus(DrawingStatus newStatus);

private:
	/*!
	 * \brief Статус в которм находится отрисовка фигуры
	 */
	DrawingStatus m_currentStatus;

	/*!
	 * \brief Признак того, надо ли сейчас отрисовывать Линию
	 */
	bool m_drawingLine;

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
