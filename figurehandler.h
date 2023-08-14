#ifndef FIGUREHANDLER_H
#define FIGUREHANDLER_H

#include <QObject>

QT_BEGIN_NAMESPACE
class Square;
class Circle;
class Triangle;
class Rectangle;
class ClickTracker;
class FigureGraphicsView;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class FigureHandler : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(FigureHandler);

public:
	/*!
	 * \brief Удаленный дефолтный деструткор
	 */
	FigureHandler() = delete;

	/*!
	 * \brief Основной конструктор
	 * \param parent - указатель на родительский класс
	 */
	explicit FigureHandler(FigureGraphicsView* parent);

	/*!
	 * \brief Основной деструктор
	 */
	~FigureHandler() override;

	/*!
	 * \brief Установить координату последнего нажатия левой кнопки мыщи
	 * \param pressedCoord - координата
	 */
	void setLastLeftMousePressed(QPointF pressedCoord);

	/*!
	 * \brief Создать и добавить новую фигуру Квадрата.
	 *        Также после вызова этого метода начинается отрисовка фигуры.
	 * \param coordinate - координата сцены, где происходит событие
	 */
	void addNewSquare(QPointF coordinate);

	/*!
	 * \brief Создать и добавить новую фигуру Прямоугольника.
	 *        Также после вызова этого метода начинается отрисовка фигуры.
	 * \param coordinate - координата сцены, где происходит событие
	 */
	void addNewRectangle(QPointF coordinate);

	/*!
	 * \brief Создать и добавить новую фигуру Круга.
	 *        Также после вызова этого метода начинается отрисовка фигуры.
	 * \param coordinate - координата сцены, где происходит событие
	 */
	void addNewCircle(QPointF coordinate);

	/*!
	 * \brief Создать и добавить новую точку для Треугольлник.
	 *        Также после вызова этого метода начинается отрисовка линии.
	 *        Если нарисована третья точка Треугольника - метод завершит
	 *        отрисовку фигуры.
	 * \param coordinate - координата сцены, где происходит событие
	 */
	void addNewTriangleDot(QPointF coordinate);

	/*!
	 * \brief Метод позволяющий продолжить отрисовку Квадрата
	 * \param coordinate - координата сцены, где происходит событие
	 */
	void continueDrawingSquare(QPointF coordinate);

	/*!
	 * \brief Метод позволяющий продолжить отрисовку Прямоугольника
	 * \param coordinate - координата сцены, где происходит событие
	 */
	void continueDrawingRectangle(QPointF coordinate);

	/*!
	 * \brief Метод позволяющий продолжить отрисовку Круга
	 * \param coordinate - координата сцены, где происходит событие
	 */
	void continueDrawingCircle(QPointF coordinate);

	/*!
	 * \brief Метод позволяющий продолжить отрисовку Треугольника
	 * \param coordinate - координата сцены, где происходит событие
	 */
	void continueDrawingTriangle(QPointF coordinate);

	/*!
	 * \brief Завершить отрисовку Квадрата
	 * \param coordinate - координата сцены, где происходит событие
	 */
	void completeSquare(QPointF coordinate);

	/*!
	 * \brief Завершить отрисовку Прямоугольника
	 * \param coordinate - координата сцены, где происходит событие
	 */
	void completeRectangle(QPointF coordinate);

	/*!
	 * \brief Завершить отрисовку Круга
	 * \param coordinate - координата сцены, где происходит событие
	 */
	void completeCircle(QPointF coordinate);

private:
	/*!
	 * \brief Указатель на Вьюшку сцены родителя
	 */
	FigureGraphicsView* m_parentView;

	/*!
	 * \brief Указатель на Квадрат с которым идет взаимодействие
	 */
	Square* m_currentSquare;

	/*!
	 * \brief Указатель на Прямоугольник с которым идет взаимодействие
	 */
	Rectangle* m_currentRectangle;

	/*!
	 * \brief Указатель на Круг с которым идет взаимодействие
	 */
	Circle* m_currentCircle;

	/*!
	 * \brief Указатель на Треугольника с которым идет взаимодействие
	 */
	Triangle* m_currentTriangle;

	/*!
	 * \brief Указатель на класс трекающий клики кнопок
	 */
	ClickTracker* m_clickHandler;
};

#endif // FIGUREHANDLER_H
