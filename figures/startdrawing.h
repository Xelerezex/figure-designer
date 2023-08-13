#ifndef STARTDRAWING_H
#define STARTDRAWING_H

#include <QtGlobal>

#include "figureaction.h"

class QGraphicsSceneMouseEvent;

class StartDrawing : public FigureAction
{
	Q_DISABLE_COPY_MOVE(StartDrawing);

public:
	StartDrawing() = delete;
	explicit StartDrawing(QGraphicsSceneMouseEvent* mouseEvent);
	~StartDrawing();

	void act(Circle* circle) override;
	void act(Square* square) override;
	void act(Triangle* triangle) override;
	void act(Rectangle* rectangle) override;

private:
	QGraphicsSceneMouseEvent* m_mouseEvent;
};

#endif // STARTDRAWING_H
