#ifndef STARTDRAWING_H
#define STARTDRAWING_H

#include <QtGlobal>
#include <QPoint>

#include "figureaction.h"

class StartDrawing : public FigureAction
{
	Q_DISABLE_COPY_MOVE(StartDrawing);

public:
	StartDrawing() = delete;
	explicit StartDrawing(const QPointF& itemCoord, const QPointF& sceneCoord);
	~StartDrawing() override;

	void act(Circle* circle) override;
	void act(Square* square) override;
	void act(Triangle* triangle) override;
	void act(Rectangle* rectangle) override;

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
	const QPointF m_defaultShift;
};

#endif // STARTDRAWING_H
