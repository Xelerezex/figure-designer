#ifndef TRIANGLESCENEOBJECT_H
#define TRIANGLESCENEOBJECT_H

#include "sceneobject.h"

class Triangle;

class TriangleSceneObject : public SceneObject
{
public:
    /*!
     * \brief Основной конструктор
     * \param id - айди объекта
     * \param figure - указатель на фигуру. Данная фигура будет владеть объектом
     *        на который указывает указатель
     */
    TriangleSceneObject(unsigned int id, Triangle* figure);

public:
    QRectF boundingRect() const override;
    void   paint(QPainter*						 painter,
                 const QStyleOptionGraphicsItem* option,
                 QWidget*						 widget) override;

private:
    /*!
     * \brief Возвращает полигон из фигуры
     * \return полигон
     */
    QPolygonF getPolygonF() const;

private:
    /*!
     * \brief Указатель на класс фигуры
     */
    std::unique_ptr<Triangle> m_triangle;
};

#endif // TRIANGLESCENEOBJECT_H
