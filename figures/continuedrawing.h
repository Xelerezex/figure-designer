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
	explicit ContinueDrawing(QPointF coordinate);
	~ContinueDrawing() override;

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

#endif // CONTINUEDRAWING_H
