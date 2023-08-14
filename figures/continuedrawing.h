#ifndef CONTINUEDRAWING_H
#define CONTINUEDRAWING_H

#include <QtGlobal>
#include <QPoint>

#include "figureaction.h"

class ContinueDrawing : public FigureAction
{
	Q_DISABLE_COPY_MOVE(ContinueDrawing);

public:
	ContinueDrawing() = delete;
	explicit ContinueDrawing(const QPointF& itemCoord);
	~ContinueDrawing() override;

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

#endif // CONTINUEDRAWING_H
