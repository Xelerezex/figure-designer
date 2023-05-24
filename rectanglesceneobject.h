#ifndef RECTANGLESCENEOBJECT_H
#define RECTANGLESCENEOBJECT_H

#include "sceneobject.h"

class Rectangle;

class RectangleSceneObject : public SceneObject
{
public:
    /*!
     * \brief Основной конструктор
     * \param id - айди объекта
     * \param figure - указатель на фигуру. Данная фигура будет владеть объектом
     *        на который указывает указатель
     */
    RectangleSceneObject(unsigned int id, Rectangle* figure);

public:
    QRectF boundingRect() const override;
    void   paint(QPainter*						 painter,
                 const QStyleOptionGraphicsItem* option,
                 QWidget*						 widget) override;

private:
    /*!
     * \brief Указатель на класс фигуры
     */
    std::unique_ptr<Rectangle> m_rectangle;
};

#endif // RECTANGLESCENEOBJECT_H
