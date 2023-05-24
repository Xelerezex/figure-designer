#include "trianglesceneobject.h"

#include "triangle.h"

#include <QPainter>
#include <QDebug>

TriangleSceneObject::TriangleSceneObject(unsigned int id, Triangle* figure)
    : SceneObject{id}
    , m_triangle{figure}
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QRectF TriangleSceneObject::boundingRect() const
{
    if (!m_triangle)
    {
        return QRectF{}.normalized();
    }

    return getPolygonF().boundingRect().normalized();
}

void TriangleSceneObject::paint(QPainter*						painter,
                                const QStyleOptionGraphicsItem* option,
                                QWidget*						widget)
{
    QPainterPath pathTitle;
    pathTitle.setFillRule(Qt::WindingFill);
    pathTitle.addPolygon(getPolygonF());

    m_triangle->setCenter(Point{pos().x(), pos().y()});

    qDebug().nospace().noquote() << "(" << m_triangle->position().x() << ", "
                                 << m_triangle->position().y() << ")";

    painter->setBrush(QBrush(Qt::black));
    painter->drawPath(pathTitle.simplified());
}

QPainterPath TriangleSceneObject::shape() const
{
    QPainterPath path;
    path.addPolygon(getPolygonF());
    return path;
}

QPolygonF TriangleSceneObject::getPolygonF() const
{
    QPointF	  first{m_triangle->point(TrianglePoint::First).x(),
                    -m_triangle->point(TrianglePoint::First).y()};

    QPointF	  second{m_triangle->point(TrianglePoint::Second).x(),
                     -m_triangle->point(TrianglePoint::Second).y()};

    QPointF	  third{m_triangle->point(TrianglePoint::Third).x(),
                    -m_triangle->point(TrianglePoint::Third).y()};

    QPolygonF polygon;
    polygon << first << second << third;

    return polygon;
}
