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

void FigureView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton)
    {
        middleMouseButtonPress(event);
    }
    else if (event->button() == Qt::LeftButton)
    {
        leftMouseButtonPress(event);
    }
    else if (event->button() == Qt::RightButton)
    {
        rightMouseButtonPress(event);
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void FigureView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton)
    {
        middleMouseButtonRelease(event);
    }
    else if (event->button() == Qt::LeftButton)
    {
        leftMouseButtonRelease(event);
    }
    else if (event->button() == Qt::RightButton)
    {
        rightMouseButtonRelease(event);
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void FigureView::middleMouseButtonPress(QMouseEvent* event)
{
    QMouseEvent* releaseEvent = new QMouseEvent(QEvent::MouseButtonRelease,
                                                event->localPos(),
                                                event->screenPos(),
                                                Qt::LeftButton,
                                                Qt::NoButton,
                                                event->modifiers());
    QGraphicsView::mouseReleaseEvent(releaseEvent);

    setDragMode(QGraphicsView::ScrollHandDrag);

    QMouseEvent* fakeEvent = new QMouseEvent(event->type(),
                                             event->localPos(),
                                             event->screenPos(),
                                             Qt::LeftButton,
                                             event->buttons() | Qt::LeftButton,
                                             event->modifiers());
    QGraphicsView::mousePressEvent(fakeEvent);
}

void FigureView::middleMouseButtonRelease(QMouseEvent* event)
{
    QMouseEvent* fakeEvent = new QMouseEvent(event->type(),
                                             event->localPos(),
                                             event->screenPos(),
                                             Qt::LeftButton,
                                             event->buttons() | Qt::LeftButton,
                                             event->modifiers());
    QGraphicsView::mouseReleaseEvent(fakeEvent);
    setDragMode(QGraphicsView::NoDrag);
}

void FigureView::leftMouseButtonPress(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
}

void FigureView::leftMouseButtonRelease(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void FigureView::rightMouseButtonPress(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
}
//---------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------//
void FigureView::rightMouseButtonRelease(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
}
//---------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------//
void FigureView::wheelEvent(QWheelEvent* event)
{
    // Вычисялем значения зума:
    const double		  zoomInFactor	= 1.25;
    const bool			  zoomClamp		= false;
    const int			  zoomStep		= 1;
    int					  zoom			= 10;
    const QPair<int, int> zoomRange		= {0, 10};
    bool				  clamped		= false;
    double				  zoomFactor	= 0;
    double				  zoomOutFactor = 1 / zoomInFactor;

    if (event->angleDelta().y() > 0)
    {
        zoomFactor = zoomInFactor;
        zoom	   = zoomStep;
    }
    else
    {
        zoomFactor = zoomOutFactor;
        zoom	   = zoomStep;
    }

    if (zoom < zoomRange.first)
    {
        zoom	= zoomRange.first;
        clamped = true;
    }

    if (zoom > zoomRange.second)
    {
        // zoom	= zoomRange.second;
        clamped = true;
    }

    // Применяем зум к сцене:
    if (!clamped || (zoomClamp == false))
    {
        scale(zoomFactor, zoomFactor);
    }
}
