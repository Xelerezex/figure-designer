#ifndef COMPLETEDRAWING_H
#define COMPLETEDRAWING_H

#include <QtGlobal>
#include <QPoint>

#include "figureaction.h"

class CompleteDrawing : public FigureAction
{
	Q_DISABLE_COPY_MOVE(CompleteDrawing);

public:
	CompleteDrawing() = delete;
	explicit CompleteDrawing(const QPointF& itemCoord);
	~CompleteDrawing() override;

	void act(Circle* circle) override;
	void act(Square* square) override;
	void act(Triangle* triangle) override;
	void act(Rectangle* rectangle) override;

private:
	/*!
	 * \brief Координаты фигуры в системе кординат Элемента Сцены
	 */
	QPointF m_itemCoord;
};

#endif // COMPLETEDRAWING_H
