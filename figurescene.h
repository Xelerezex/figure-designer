#pragma once

#ifndef FIGURESCENE_H
#define FIGURESCENE_H

#include <QGraphicsScene>

class FigureScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit FigureScene(QObject* parent = nullptr);
};

#endif // FIGURESCENE_H
