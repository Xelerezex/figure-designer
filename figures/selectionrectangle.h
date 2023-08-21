#ifndef SELECTIONRECTANGLE_H
#define SELECTIONRECTANGLE_H

#include "figurebase.h"

/*!
 * \brief Класс представления прямоугольника выделения фигур
 */
class SelectionRectangle : public FigureBase
{
	Q_DISABLE_COPY_MOVE(SelectionRectangle);

public:
	/*!
	 * \brief Основной конструктор
	 * \param fileMenu - указатель на основное Меню
	 * \param parent - указаетль на родительский класс
	 */
	explicit SelectionRectangle(QMenu*		   fileMenu,
								QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~SelectionRectangle() override;

	/*!
	 * \brief Возвращает тип фигуры
	 * \return тип фигуры
	 */
	[[nodiscard]] int type() const override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие начала отрисовки
	 *        прямоугольника (visitor)
	 * \param startDrawing - класс действия начала отрисовки прямоугольника
	 */
	void act(StartDrawing&& startDrawing) override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие продолжения
	 *        отрисовки прямоугольника (visitor)
	 * \param startDrawing - класс действия продолжения отрисовки прямоугольника
	 */
	void act(ContinueDrawing&& continueDrawing) override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить действие завершения
	 *        отрисовки прямоугольника (visitor)
	 * \param startDrawing - класс действия завершения отрисовки прямоугольника
	 */
	void act(CompleteDrawing&& completeDrawing) override;

	/*!
	 * \brief Метод вызываемый, когда нужно совершить сериализацию (visitor)
	 * \param serialize - класс действия сериализации в JSON формат
	 */
	void act(SerializeToJson&& serialize) override;

	/*!
	 * \brief Возвращает начальную точку, от которой началась отрисовка
	 * \return координата
	 */
	[[nodiscard]] const QPointF& leftTop();

	/*!
	 * \brief Установить первую точку для начала отрисовки
	 * \param newLeftTop - новая координата
	 */
	void setLeftTop(const QPointF& newLeftTop);

	/*!
	 * \brief Получить координаты второй точки
	 * \return координаты
	 */
	[[nodiscard]] const QPointF& destination() const;

	/*!
	 * \brief Установить координаты второй точки фигуры
	 * \param newCenter - новые координаты второй точки
	 */
	void setDestination(const QPointF& newDestination);

	/*!
	 * \brief Функция определяет границы фигуры
	 * \return
	 */
	[[nodiscard]] QRectF boundingRect() const override;

	/*!
	 * \brief Функция занимается отрисовкой фигуры
	 * \param painter - указатель на отрисовщик для Фигуры
	 * \param option - указатель на стиль для Фигуры
	 * \param widget - опционально, указатель на виджет, где должна происходить
	 *                 отрисовка
	 */
	void paint(QPainter*					   painter,
			   const QStyleOptionGraphicsItem* option,
			   QWidget*						   widget) override;

private:
	/*!
	 * \brief Метод высчитывает границы данного Квадрата относительно центра
	 *        и второй точки
	 * \return границы квадрата
	 */
	[[nodiscard]] QRectF countFigure() const override;

private:
	/*!
	 * \brief Коориднаты левой верхней точки, от которой начинается отрисовка
	 */
	QPointF m_leftTop;

	/*!
	 * \brief Координаты второй Точки, нужной для построения Фигуры
	 */
	QPointF m_destination;
};

#endif // SELECTIONRECTANGLE_H
