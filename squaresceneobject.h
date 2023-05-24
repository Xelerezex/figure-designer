#ifndef SQUARESCENEOBJECT_H
#define SQUARESCENEOBJECT_H

#include "sceneobject.h"

class Square;

class SquareSceneObject : public SceneObject
{
public:
    /*!
     * \brief Основной конструктор
     * \param id - айди объекта
     * \param figure - указатель на фигуру. Данная фигура будет владеть объектом
     *        на который указывает указатель
     */
    SquareSceneObject(unsigned int id, Square* figure);

public:
    QRectF boundingRect() const override;
    void   paint(QPainter*						 painter,
                 const QStyleOptionGraphicsItem* option,
                 QWidget*						 widget) override;

private:
    /*!
     * \brief Указатель на класс фигуры
     */
    std::unique_ptr<Square> m_square;
};

#endif // SQUARESCENEOBJECT_H
