#ifndef COMPLETEDRAWING_H
#define COMPLETEDRAWING_H

#include <QtGlobal>

#include "figureaction.h"

class QGraphicsSceneMouseEvent;

class CompleteDrawing : public FigureAction
{
	Q_DISABLE_COPY_MOVE(CompleteDrawing);

public:
	CompleteDrawing() = delete;
	explicit CompleteDrawing(QGraphicsSceneMouseEvent* mouseEvent);
	~CompleteDrawing();

	void act(Circle* circle) override;
	void act(Square* square) override;
	void act(Triangle* triangle) override;
	void act(Rectangle* rectangle) override;

private:
	QGraphicsSceneMouseEvent* m_mouseEvent;
};

#endif // COMPLETEDRAWING_H
