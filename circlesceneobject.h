#pragma once

#ifndef CIRCLESCENEOBJECT_H
#define CIRCLESCENEOBJECT_H

#include "sceneobject.h"

class Circle;

class CircleSceneObject : public SceneObject
{
public:
    /*!
     * \brief Основной конструктор
     * \param id - айди объекта
     * \param figure - указатель на фигуру. Данная фигура будет владеть объектом
     *        на который указывает указатель
     */
    CircleSceneObject(unsigned int id, Circle* figure);

public:
    QRectF		 boundingRect() const override;
    void		 paint(QPainter*					   painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget*						   widget) override;
    QPainterPath shape() const override;

private:
    /*!
     * \brief Указатель на класс фигуры
     */
    std::unique_ptr<Circle> m_circle;
};

#endif // CIRCLESCENEOBJECT_H
