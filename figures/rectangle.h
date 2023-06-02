#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figures.h"

/*!
 * \brief Имена вершин в прямоугольнике
 */
enum class RectanglePoint : int8_t
{
    First,
    Second,
    Third,
    Fourth
};

class Rectangle : public Figures
{
public:
    /*!
     * \brief основной конструктор
     * \param
     */
    explicit Rectangle(double width, double height);

    /*!
     *  \brief Дефолтный деструткор
     */
    ~Rectangle() = default;

    /*!
     * \brief Удаленные операторы
     */
    Rectangle()						  = delete;
    Rectangle(const Rectangle&)		  = delete;
    Rectangle(Rectangle&&)			  = delete;
    Rectangle& operator=(Rectangle&)  = delete;
    Rectangle& operator=(Rectangle&&) = delete;

    /*!
     * \brief Метод возвращает длину высоты
     * \return длина
     */
    double height() const;

    /*!
     * \brief Метод возвращает длину ширины
     * \return длина
     */
    double width() const;

    /*!
     * \brief Получает на вход имя точки и возвращает ее координату
     * \param point - тип точки
     * \return координаты
     */
    Point point(RectanglePoint point) const;

private:
    /*!
     * \brief Метод высчитывающий стартовую позицию фигуры
     * \param width - ширина прямоугольник
     * \param height - высота прямоугольника
     */
    void calculateStartCoordinate(double width, double height);

private:
    /*!
     * \brief Длина одной сторонры
     */
    double m_width;
    double m_height;

    /*!
     * \brief Относительные координаты фигуры
     *
     *    first------------second
     *    |                     |
     *    |                     |
     *    |                     |
     *    |                     |
     *    fourth------------third
     *
     */
    Point m_first;
    Point m_second;
    Point m_third;
    Point m_fourth;
};

#endif // RECTANGLE_H
