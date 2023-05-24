#ifndef POINT_H
#define POINT_H

class Point
{
public:
    /*!
     * \brief Основной конструктор
     * \param x - значение точки X
     * \param y - значение точки Y
     */
    explicit Point(double x = 0, double y = 0);

    /*!
     * \brief возвращает значение X
     * \return целочисленое значение
     */
    double x() const;

    /*!
     * \brief возвращает значение Y
     * \return целочисленое значение
     */
    double y() const;

    /*!
     * \brief Установить значение по X
     * \param x
     */
    void setX(double x);

    /*!
     * \brief Установить значение по Y
     * \param y
     */
    void setY(double y);

    /*!
     * \brief Установить сразу две координаты
     * \param x
     * \param y
     */
    void setPosition(double x, double y);

private:
    /*!
     * \brief Позиция в точке X
     */
    double m_positionX;

    /*!
     * \brief Позиция в точке Y
     */
    double m_positionY;
};

#endif // POINT_H
