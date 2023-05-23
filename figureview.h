#pragma once

#ifndef FIGUREVIEW_H
#define FIGUREVIEW_H

#include <QGraphicsView>
#include <QObject>

class FigureView : public QGraphicsView
{
public:
    explicit FigureView(QGraphicsScene* scene, QWidget* parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;

    virtual void middleMouseButtonPress(QMouseEvent* event);
    virtual void middleMouseButtonRelease(QMouseEvent* event);
    virtual void leftMouseButtonPress(QMouseEvent* event);
    virtual void leftMouseButtonRelease(QMouseEvent* event);
    virtual void rightMouseButtonPress(QMouseEvent* event);
    virtual void rightMouseButtonRelease(QMouseEvent* event);
};

#endif // FIGUREVIEW_H
