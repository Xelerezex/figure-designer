#pragma once

#ifndef FIGURES_H
#define FIGURES_H

#include "point.h"

class Figures
{
public:
    /*!
     * \brief Оснговной конструктор
     * \param x - позиция фигуры по X
     * \param y - позиция фигуры по Y
     */
    explicit Figures(Point p = Point{0, 0});

    /*!
     * \brief Удаленные операторы
     */
    Figures()					  = delete;
    Figures(const Figures&)		  = delete;
    Figures(Figures&&)			  = delete;
    Figures& operator=(Figures&)  = delete;
    Figures& operator=(Figures&&) = delete;

    /*!
     * \brief Вирутальный деструктор
     */
    virtual ~Figures();

    /*!
     * \brief Функция высчитывает центр фигуры
     * \return координаты центра
     */
    virtual Point calculateCenter() const = 0;

private:
    Point m_position;
};

#endif // FIGURES_H
