#pragma once

#ifndef FIGURES_H
#define FIGURES_H

#include "point.h"

#include <cstdint>

/*!
 * \brief тип фигуры
 */
enum class FigureType : int8_t
{
    Square = 0,
};

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
     * \brief Виртуальный деструктор
     */
    virtual ~Figures();

    /*!
     * \brief Вернуть центральную точку фигуры
     * \return точка в пространстве
     */
    Point position() const;

    /*!
     * \brief метод устанавливает позицию центра
     * \param position - координата центра
     */
    void setCenter(Point position);

private:
    /*!
     * \brief Позиция центра фигуры
     */
    Point m_position;
};

#endif // FIGURES_H
