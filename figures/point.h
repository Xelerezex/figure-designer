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
    explicit Point(int x = 0, int y = 0);

    /*!
     * \brief возвращает значение X
     * \return целочисленое значение
     */
    int x() const;

    /*!
     * \brief возвращает значение Y
     * \return целочисленое значение
     */
    int y() const;

    /*!
     * \brief Установить значение по X
     * \param x
     */
    void setX(int x);

    /*!
     * \brief Установить значение по Y
     * \param y
     */
    void setY(int y);

    /*!
     * \brief Установить сразу две координаты
     * \param x
     * \param y
     */
    void setPosition(int x, int y);

private:
    int m_positionX;
    int m_positionY;
};

#endif // POINT_H
