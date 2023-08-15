#ifndef CONTINUEDRAWING_H
#define CONTINUEDRAWING_H

#include <QtGlobal>
#include <QPoint>

#include "figureaction.h"

/*!
 * \brief Класс представляющий действие продолжения отрисовки Фигур
 */
class ContinueDrawing : public FigureAction
{
	Q_DISABLE_COPY_MOVE(ContinueDrawing);

public:
	/*!
	 * \brief Удаленный дефолтный конструткор
	 */
	ContinueDrawing() = delete;

	/*!
	 * \brief Дефолтный кеонстуктор
	 * \param itemCoord - координаты фигуры в системе кординат Элемента Сцены
	 */
	explicit ContinueDrawing(const QPointF& itemCoord);

	/*!
	 *  \brief Дефолтный деструктор
	 */
	~ContinueDrawing() override;

	/*!
	 * \brief Действие продолжения отрисовки для класса представления Круга
	 */
	void act(Circle* circle) override;

	/*!
	 * \brief Действие продолжения отрисовки для класса представления Квадрата
	 */
	void act(Square* square) override;

	/*!
	 * \brief Действие продолжения отрисовки для класса представления
	 *        Треугольника
	 */
	void act(Triangle* triangle) override;

	/*!
	 * \brief Действие продолжения отрисовки для класса представления
	 *        Прямоугольника
	 */
	void act(Rectangle* rectangle) override;

	/*!
	 * \brief Действие продолжения отрисовки для класса представления
	 *        Прямоугольника Выделения
	 */
	void act(class SelectionRectangle* selectRect) override;

private:
	/*!
	 * \brief Координаты фигуры в системе кординат Элемента Сцены
	 */
	QPointF m_itemCoord;
};

#endif // CONTINUEDRAWING_H
