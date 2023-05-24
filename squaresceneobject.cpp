#include "squaresceneobject.h"

#include "square.h"

#include <QPainter>
#include <QDebug>

SquareSceneObject::SquareSceneObject(unsigned int id, Square* figure)
    : SceneObject{id}
    , m_square{figure}
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QRectF SquareSceneObject::boundingRect() const
{
    if (!m_square)
    {
        return QRectF{}.normalized();
    }

    QRectF rectangle{m_square->point(SquarePoint::Fourth).x(),
                     m_square->point(SquarePoint::Fourth).y(),
                     m_square->side(),
                     m_square->side()};

    return rectangle.normalized();
}

void SquareSceneObject::paint(QPainter*						  painter,
                              const QStyleOptionGraphicsItem* option,
                              QWidget*						  widget)
{
    QPainterPath pathTitle;
    pathTitle.setFillRule(Qt::WindingFill);
    pathTitle.addRect(m_square->point(SquarePoint::Fourth).x(),
                      m_square->point(SquarePoint::Fourth).y(),
                      m_square->side(),
                      m_square->side());

    m_square->setCenter(Point{pos().x(), pos().y()});

    qDebug().nospace().noquote() << "(" << m_square->position().x() << ", "
                                 << m_square->position().y() << ")";

    painter->setBrush(QBrush(Qt::black));
    painter->drawPath(pathTitle.simplified());
}
