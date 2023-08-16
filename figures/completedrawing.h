#ifndef COMPLETEDRAWING_H
#define COMPLETEDRAWING_H

#include <QtGlobal>
#include <QPoint>

#include "figureaction.h"

/*!
 * \brief Класс представляющий действие завершения отрисовки Фигур
 */
class CompleteDrawing : public FigureAction
{
	Q_DISABLE_COPY_MOVE(CompleteDrawing);

public:
	/*!
	 * \brief Удаленный дефолтный конструткор
	 */
	CompleteDrawing() = delete;

	/*!
	 * \brief Дефолтный кеонстуктор
	 * \param itemCoord - координаты фигуры в системе кординат Элемента Сцены
	 */
	explicit CompleteDrawing(const QPointF& itemCoord);

	/*!
	 *  \brief Дефолтный деструктор
	 */
	~CompleteDrawing() override;

	/*!
	 * \brief Действие завершения отрисовки для класса представления Круга
	 */
	void act(Circle* circle) override;

	/*!
	 * \brief Действие завершения отрисовки для класса представления Квадрата
	 */
	void act(Square* square) override;

	/*!
	 * \brief Действие завершения отрисовки для класса представления
	 *       Треугольника
	 */
	void act(Triangle* triangle) override;

	/*!
	 * \brief Действие завершения отрисовки для класса представления
	 *        Прямоугольника
	 */
	void act(Rectangle* rectangle) override;

	/*!
	 * \brief Действие начала отрисовки для класса представления
	 *        Прямоугольника Выделения
	 */
	void act(class SelectionRectangle* selectRect) override;

private:
	/*!
	 * \brief Координаты фигуры в системе кординат Элемента Сцены
	 */
	QPointF m_itemCoord;
};

#endif // COMPLETEDRAWING_H
