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
	explicit StartDrawing(QPointF coordinate);
	~StartDrawing() override;

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

#endif // STARTDRAWING_H
