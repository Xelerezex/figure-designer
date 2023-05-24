#ifndef SQUARESCENEOBJECT_H
#define SQUARESCENEOBJECT_H

#include "sceneobject.h"

class Square;

class SquareSceneObject : public SceneObject
{
public:
    SquareSceneObject(unsigned int id, Square* figure);

public:
	QRectF boundingRect() const override;
    void   paint(QPainter*						 painter,
                 const QStyleOptionGraphicsItem* option,
                 QWidget*						 widget) override;

private:
    std::unique_ptr<Square> m_square;
};

#endif // SQUARESCENEOBJECT_H
