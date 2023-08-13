#ifndef FIGUREBASE_H
#define FIGUREBASE_H

#include <QGraphicsItem>

class StartDrawing;
class ContinueDrawing;
class CompleteDrawing;

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

	virtual void act(StartDrawing&& startDrawing)	 = 0;
	virtual void act(ContinueDrawing&& startDrawing) = 0;
	virtual void act(CompleteDrawing&& startDrawing) = 0;

	/*!
	 * \brief Метод должен вызываться когда начинается первичное создание
	 *        объекта и его первичная отрисовка.
	 */
	void startCreating();

	/*!
	 * \brief Метод должен быть вызван при завершении создания и первичной
	 *        настрйоки объекта
	 */
	void completeCreating();

	/*!
	 * \brief Метод возвращает признак полного создания элемента
	 * \return true - если создание завершено
	 */
	bool isFullyCreated() const;

protected:
	/*!
	 * \brief Основной конструктор
	 * \param parent - указатель на родительский класс
	 */
	explicit FigureBase(QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Метод высчитывает границы данного Квадрата относительно центра
	 *        и второй точки
	 * \return границы квадрата
	 */
	virtual QRectF countFigure() const = 0;

private:
	/*!
	 * \brief Жизненый цикл объекта Сцены
	 */
	enum LifeCycle
	{
		NotExisting,
		Creating,
		FullyCreated
	};

	/*!
	 * \brief Текущий жизненый цикл
	 */
	LifeCycle m_currentCycle;
};

#endif // FIGUREBASE_H
