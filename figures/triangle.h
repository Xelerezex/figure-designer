#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figures.h"

/*!
 * \brief Имена вершин в квадрате
 */
enum class TrianglePoint : int8_t
{
    First,
    Second,
    Third
};

class Triangle : public Figures
{
public:
    /*!
     * \brief основной конструктор
     * \param firstSide - координата первой вершины
     * \param secondSide - координата второй вершины
     * \param thirdSide - координата третьей вершины
     */
    Triangle(Point first, Point second, Point third);

    /*!
     *  \brief Дефолтный деструткор
     */
    ~Triangle() = default;

    /*!
     * \brief Удаленные операторы
     */
    Triangle()						= delete;
    Triangle(const Triangle&)		= delete;
    Triangle(Triangle&&)			= delete;
    Triangle& operator=(Triangle&)	= delete;
    Triangle& operator=(Triangle&&) = delete;

    /*!
     * \brief Получает на вход имя точки и возвращает ее координату
     * \param point - тип точки
     * \return координаты
     */
    Point point(TrianglePoint point) const;

private:
    /*!
     * \brief Метод проверяющий возможно дли создать такой треугольник
     * \param firstSide - координата первой вершины
     * \param secondSide - координата второй вершины
     * \param thirdSide - координата третьей вершины
     */
    bool checkExisting(Point first, Point second, Point third);

    /*!
     * \brief Метод для нахождения расстояния между двумя точками
     * \param first - первая точка
     * \param second - второая точка
     * \return значение
     */
    double distance(Point first, Point second);

private:
    /*!
     * \brief Относительные координаты фигуры
     *
     *           first
     *            |\
     *          |    \
     *        |        \
     *      |            \
     *    second--------third
     *
     */
    Point m_first;
    Point m_second;
    Point m_third;
};

#endif // TRIANGLE_H
