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
	explicit CompleteDrawing(QPointF coordinate);
	~CompleteDrawing() override;

	void act(Circle* circle) override;
	void act(Square* square) override;
	void act(Triangle* triangle) override;
	void act(Rectangle* rectangle) override;

private:
	/*!
	 * \brief координата, в которой произошло данное действие
	 */
	QPointF m_coordinate;
};

#endif // COMPLETEDRAWING_H
