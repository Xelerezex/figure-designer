#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figurebase.h"

/*!
 * \brief Базовый класс представления треугольника
 */
class Triangle : public FigureBase
{
	Q_DISABLE_COPY_MOVE(Triangle);

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
	~Triangle() override;

	/*!
	 * \brief Возвращает тип фигуры
	 * \return тип фигуры
	 */
	int type () const override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие начала отрисовки
	 *        треугольника (visitor)
	 * \param startDrawing - класс действия начала отрисовки треугольника
	 */
	void act(StartDrawing&& startDrawing) override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие продолжения
	 *        отрисовки треугольника (visitor)
	 * \param startDrawing - класс действия продолжения отрисовки треугольника
	 */
	void act(ContinueDrawing&& continueDrawing) override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие завершения
	 *        отрисовки треугольника (visitor)
	 * \param startDrawing - класс действия завершения отрисовки треугольника
	 */
	void act(CompleteDrawing&& completeDrawing) override;

	/* ------------- Методы для взаимодействия с первой точкой ------------- */
	/*!
	 * \brief Метод возвращает координаты Первой точки
	 * \return координаты точки
	 */
	[[nodiscard]] QPointF first() const;

	/*!
	 * \brief Установить координаты первой точки фигуры
	 * \param newCenter - новые координаты первой точки
	 */
	void setFirst(QPointF newFirst);

	/*!
	 * \brief Метод проверяет установлена ли первая точка Треугольника
	 * \return true - если у первой точки уже есть координата
	 */
	[[nodiscard]] bool isFirstDrawn() const;

	/* ------------- Методы для взаимодействия со второй точкой ------------ */
	/*!
	 * \brief Метод возвращает координаты Второй точки
	 * \return координаты точки
	 */
	[[nodiscard]] QPointF second() const;

	/*!
	 * \brief Установить координаты второй точки фигуры
	 * \param newCenter - новые координаты второй точки
	 */
	void setSecond(QPointF newSecond);

	/*!
	 * \brief Метод проверяет установлена ли вторая точка Треугольника
	 * \return true - если у второй точки уже есть координата
	 */
	[[nodiscard]] bool isSecondDrawn() const;

	/* ------------- Методы для взаимодействия с третьей точкой ------------ */
	/*!
	 * \brief Метод возвращает координаты Третьей точки
	 * \return координаты точки
	 */
	[[nodiscard]] QPointF third() const;

	/*!
	 * \brief Установить координаты третьей точки фигуры
	 * \param newCenter - новые координаты третьей точки
	 */
	void setThird(QPointF newThird);

	/*!
	 * \brief Метод проверяет установлена ли третья точка Треугольника
	 * \return true - если у третьей точки уже есть координата
	 */
	[[nodiscard]] bool isThirdDrawn() const;

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
	[[nodiscard]] bool isLineDrawing() const;

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
	[[nodiscard]] QPolygonF countPolygon() const;

	/*!
	 * \brief Метод высчитывает границы данного Квадрата относительно центра
	 *        и второй точки
	 * \return границы квадрата
	 */
	[[nodiscard]] QRectF countFigure() const override;

	/*!
	 * \brief Установить статус отрисовки треугольника
	 * \param newStatus - новый статус
	 */
	void setStatus(DrawingStatus newStatus);

	/*!
	 * \brief Метод высчитывает центр Треугольника.
	 * \warning Вызывать только, когда заданы все три точки
	 * \return координаты центра
	 */
	QPointF countCenter() const;

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
