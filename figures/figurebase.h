#ifndef FIGUREBASE_H
#define FIGUREBASE_H

#include <QGraphicsItem>

class FigureBase : public QGraphicsItem
{
	Q_DISABLE_COPY_MOVE(FigureBase);

public:
	/*!
	 * \brief Удаленный дефолтный конструктор
	 */
	FigureBase() = delete;

	/*!
	 * \brief Дефолтный деструктор
	 */
	~FigureBase() override;

protected:
	/*!
	 * \brief Основной конструктор
	 * \param parent - указатель на родительский класс
	 */
	explicit FigureBase(QGraphicsItem* parent = nullptr);
};

#endif // FIGUREBASE_H
