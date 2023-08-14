#ifndef FIGUREACTION_H
#define FIGUREACTION_H

class Circle;
class Square;
class Triangle;
class Rectangle;

/*!
 * \brief Базовый класс действия представления фигур
 */
class FigureAction
{
public:
	/*!
	 * \brief Базовый дефолтный конструткор
	 */
	FigureAction() = default;

	/*!
	 * \brief Удаленный опреаторы/конструткоры Копирования/Присваивания
	 */
	FigureAction(const FigureAction&)			 = delete;
	FigureAction& operator=(const FigureAction&) = delete;
	FigureAction(FigureAction&&)				 = delete;
	FigureAction& operator=(FigureAction&&)		 = delete;

	/*!
	 * \brief Базовый виртуальный деструктор
	 */
	virtual ~FigureAction();

	/*!
	 * \brief Действие для класса представления Круга
	 */
	virtual void act(class Circle*) = 0;

	/*!
	 * \brief Действие для класса представления Квадрата
	 */
	virtual void act(class Square*) = 0;

	/*!
	 * \brief Действие для класса представления Треугольника
	 */
	virtual void act(class Triangle*) = 0;

	/*!
	 * \brief Действие для класса представления Прямоугольника
	 */
	virtual void act(class Rectangle*) = 0;
};

#endif // FIGUREACTION_H
