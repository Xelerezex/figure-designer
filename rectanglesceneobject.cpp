#include "rectanglesceneobject.h"

#include "rectangle.h"

#include <QPainter>
#include <QDebug>

RectangleSceneObject::RectangleSceneObject(unsigned int id, Rectangle* figure)
    : SceneObject{id}
    , m_rectangle{figure}
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QRectF RectangleSceneObject::boundingRect() const
{
    if (!m_rectangle)
    {
        return QRectF{}.normalized();
    }

    QRectF rectangle{m_rectangle->point(RectanglePoint::Fourth).x(),
                     m_rectangle->point(RectanglePoint::Fourth).y(),
                     m_rectangle->width(),
                     m_rectangle->height()};

    return rectangle.normalized();
}

void RectangleSceneObject::paint(QPainter*						 painter,
                                 const QStyleOptionGraphicsItem* option,
                                 QWidget*						 widget)
{
    QPainterPath pathTitle;
    pathTitle.setFillRule(Qt::WindingFill);
    pathTitle.addRect(m_rectangle->point(RectanglePoint::Fourth).x(),
                      m_rectangle->point(RectanglePoint::Fourth).y(),
                      m_rectangle->width(),
                      m_rectangle->height());

    m_rectangle->setCenter(Point{pos().x(), pos().y()});

    qDebug().nospace().noquote() << "(" << m_rectangle->position().x() << ", "
                                 << m_rectangle->position().y() << ")";

    painter->setBrush(QBrush(Qt::black));
    painter->drawPath(pathTitle.simplified());
}
