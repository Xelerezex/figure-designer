#ifndef SQUARESCENEOBJECT_H
#define SQUARESCENEOBJECT_H

#include "sceneobject.h"

class SquareSceneObject : public SceneObject
{
public:
	SquareSceneObject(unsigned int id, Figures* figure, QGraphicsItem* graphics);

public:
	QRectF boundingRect() const override;
	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
			   QWidget *widget) override;
};

#endif // SQUARESCENEOBJECT_H
