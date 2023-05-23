#pragma once

#ifndef FIGUREVIEW_H
#define FIGUREVIEW_H

#include <QGraphicsView>
#include <QObject>

class FigureView : public QGraphicsView
{
public:
    explicit FigureView(QGraphicsScene* scene, QWidget* parent = nullptr);
};

#endif // FIGUREVIEW_H
