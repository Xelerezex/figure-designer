#include "squaresceneobject.h"

#include "figures.h"

SquareSceneObject::SquareSceneObject(unsigned int id, Figures *figure, QGraphicsItem* graphics)
	: SceneObject{id, figure, graphics}
{

}


QRectF SquareSceneObject::boundingRect() const
{

}

void SquareSceneObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}
