#include "figureview.h"

#include <QMouseEvent>

FigureView::FigureView(QGraphicsScene* scene, QWidget* parent)
{
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing
                   | QPainter::SmoothPixmapTransform);

    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Hides scrollbar from main Window:
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}
