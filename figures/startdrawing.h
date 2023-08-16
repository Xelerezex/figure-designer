#ifndef STARTDRAWING_H
#define STARTDRAWING_H

#include <QtGlobal>
#include <QPoint>

#include "figureaction.h"

/*!
 * \brief Класс представляющий действие начала отрисовки Фигур
 */
class StartDrawing : public FigureAction
{
	Q_DISABLE_COPY_MOVE(StartDrawing);

public:
	/*!
	 * \brief Удаленный дефолтный конструткор
	 */
	StartDrawing() = delete;
	/*!
	 * \brief Дефолтный кеонстуктор
	 * \param itemCoord - координаты фигуры в системе кординат Элемента Сцены
	 * \param sceneCoord - Дефолтный сдвиг для первичной отрисовки фигуры
	 */
	explicit StartDrawing(const QPointF& itemCoord, const QPointF& sceneCoord);

	/*!
	 *  \brief Дефолтный деструктор
	 */
	~StartDrawing() override;

	/*!
	 * \brief Действие начала отрисовки для класса представления Круга
	 */
	void act(Circle* circle) override;

	/*!
	 * \brief Действие начала отрисовки для класса представления Квадрата
	 */
	void act(Square* square) override;

	/*!
	 * \brief Действие начала отрисовки для класса представления
	 *        Треугольника
	 */
	void act(Triangle* triangle) override;

	/*!
	 * \brief Действие начала отрисовки для класса представления
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

	/*!
	 * \brief Координаты фигуры на Сцене
	 */
	QPointF m_sceneCoord;

	/*!
	 * \brief Дефолтный сдвиг для первичной отрисовки фигуры
	 */
	QPointF m_defaultShift;
};

#endif // STARTDRAWING_H
