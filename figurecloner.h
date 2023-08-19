#ifndef FIGURECLONER_H
#define FIGURECLONER_H

#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QMenu;
class Square;
class Circle;
class Triangle;
class Rectangle;
class QGraphicsItem;
QT_END_NAMESPACE

/*!
 * \brief Небольшой класс-обертка с фабричными методами клонирования Фигур
 */
class FigureCloner
{
public:
	/*!
	 * \brief Дефолтный конструктор
	 */
	FigureCloner() = default;

	/*!
	 * \brief Метод для клонирования нового объекта Квадрата
	 * \param item - указатель на базовый класс конкретной фигуры
	 * \return указатель на Квадрат
	 */
	static Square* cloneSquare(QMenu* fileMenu, QGraphicsItem* item);

	/*!
	 * \brief Метод для клонирования нового объекта Прямоугольника
	 * \param item - указатель на базовый класс конкретной фигуры
	 * \return указатель на Прямоугольник
	 */
	static Rectangle* cloneRectangle(QMenu* fileMenu, QGraphicsItem* item);

	/*!
	 * \brief Метод для клонирования нового объекта Треугольника
	 * \param item - указатель на базовый класс конкретной фигуры
	 * \return указатель на Треугольник
	 */
	static Triangle* cloneTriangle(QMenu* fileMenu, QGraphicsItem* item);

	/*!
	 * \brief Метод для клонирования нового объекта Окружности
	 * \param item - указатель на базовый класс конкретной фигуры
	 * \return указатель на Окружность
	 */
	static Circle* cloneCircle(QMenu* fileMenu, QGraphicsItem* item);
};

#endif // FIGURECLONER_H
