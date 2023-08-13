#ifndef CONTINUEDRAWING_H
#define CONTINUEDRAWING_H

#include <QtGlobal>

#include "figureaction.h"

class QGraphicsSceneMouseEvent;

class ContinueDrawing : public FigureAction
{
	Q_DISABLE_COPY_MOVE(ContinueDrawing);

public:
	ContinueDrawing() = delete;
	explicit ContinueDrawing(QGraphicsSceneMouseEvent* mouseEvent);
	~ContinueDrawing();

	void act(Circle* circle) override;
	void act(Square* square) override;
	void act(Triangle* triangle) override;
	void act(Rectangle* rectangle) override;

private:
	QGraphicsSceneMouseEvent* m_mouseEvent;
};

#endif // CONTINUEDRAWING_H
