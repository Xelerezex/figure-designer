#include "circlesceneobject.h"

#include "circle.h"

#include <QPainter>
#include <QDebug>

CircleSceneObject::CircleSceneObject(unsigned int id, Circle* figure)
    : SceneObject{id}
    , m_circle{figure}
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QRectF CircleSceneObject::boundingRect() const
{
    if (!m_circle)
    {
        return QRectF{}.normalized();
    }

    double radius	= m_circle->radius();
    double diameter = radius * 2;
    QRectF circle{-radius, -radius, diameter, diameter};

    return circle.normalized();
}

void CircleSceneObject::paint(QPainter*						  painter,
                              const QStyleOptionGraphicsItem* option,
                              QWidget*						  widget)
{
    QPainterPath pathTitle;
    pathTitle.setFillRule(Qt::WindingFill);
    pathTitle.addEllipse(QPointF{}, m_circle->radius(), m_circle->radius());

    m_circle->setCenter(Point{pos().x(), pos().y()});

    qDebug().nospace().noquote() << "(" << m_circle->position().x() << ", "
                                 << m_circle->position().y() << ")";

    painter->setBrush(QBrush(Qt::black));
    painter->drawPath(pathTitle.simplified());
}

QPainterPath CircleSceneObject::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
