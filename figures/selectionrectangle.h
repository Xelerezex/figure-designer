#ifndef SELECTIONRECTANGLE_H
#define SELECTIONRECTANGLE_H

#include "rectangle.h"

/*!
 * \brief Класс представления прямоугольника выделения фигур
 */
class SelectionRectangle : public Rectangle
{
	Q_DISABLE_COPY_MOVE(SelectionRectangle);

public:
	/*!
	 * \brief Основной конструктор
	 * \param parent - указаетль на родительский класс
	 */
	explicit SelectionRectangle(QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~SelectionRectangle() override;
};

#endif // SELECTIONRECTANGLE_H
