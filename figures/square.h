#ifndef SQUARE_H
#define SQUARE_H

#include "figures.h"

/*!
 * \brief Имена вершин в квадрате
 */
enum class SquarePoint : int8_t
{
    First,
    Second,
    Third,
    Fourth
};

class Square : public Figures
{
public:
    /*!
     * \brief Square - основной конструктор
     * \param side - длина одной стороны прямоугольника
     */
    explicit Square(double side);

    /*!
     *  \brief Дефолтный деструткор
     */
    ~Square() = default;

    /*!
     * \brief Удаленные операторы
     */
    Square()					= delete;
    Square(const Square&)		= delete;
    Square(Square&&)			= delete;
    Square& operator=(Square&)	= delete;
    Square& operator=(Square&&) = delete;

    /*!
     * \brief Метод возвращает длину одной стороны
     * \return длина
     */
    double side() const;

    /*!
     * \brief Получает на вход имя точки и возвращает ее координату
     * \param point - тип точки
     * \return координаты
     */
    Point point(SquarePoint point) const;

private:
    /*!
     * \brief Метод высчитывающий стартовую позицию фигуры
     * \param side
     */
    void calculateStartCoordinate(double side);

private:
    /*!
     * \brief Длина одной линии
     */
    double m_side;

    /*!
     * \brief Относительные координаты размера фигуры
     *
     *    first--------second
     *      |             |
     *      |             |
     *      |             |
     *      |             |
     *    fourth--------third
     *
     */
    Point m_first;
    Point m_second;
    Point m_third;
    Point m_fourth;
};

#endif // SQUARE_H
