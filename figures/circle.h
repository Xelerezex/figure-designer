#ifndef CIRCLE_H
#define CIRCLE_H

#include "figures.h"

class Circle : public Figures
{
public:
    /*!
     * \brief основной конструктор
     * \param длина радиуса
     */
    explicit Circle(double radPoint);

    /*!
     *  \brief Дефолтный деструткор
     */
    ~Circle() = default;

    /*!
     * \brief Удаленные операторы
     */
    Circle()					= delete;
    Circle(const Circle&)		= delete;
    Circle(Circle&&)			= delete;
    Circle& operator=(Circle&)	= delete;
    Circle& operator=(Circle&&) = delete;

    /*!
     * \brief Метод возвращает длину радиуса
     * \return длина
     */
    double radius() const;

private:
    /*!
     * \brief длина радиуса
     */
    double m_radius;
};

#endif // CIRCLE_H
