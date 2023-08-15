#ifndef CLICKTRACKER_H
#define CLICKTRACKER_H

#include <QObject>
#include <QPoint>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

/*!
 * \brief Данный класс наблюдает за координатами, в которых были зафиксированы
 *        MouseEvents
 */
class ClickTracker : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(ClickTracker);

public:
	/*!
	 * \brief Удаленный дефолтный конструктор
	 */
	ClickTracker() = delete;

	/*!
	 * \brief Основной конструктор
	 * \param parent - указатель на родительский класс
	 */
	explicit ClickTracker(QObject* parent);

	/*!
	 * \brief Основной деструктор
	 */
	~ClickTracker() override;

	/*!
	 * \brief Получить координату где последний раз была нажата левая кнопка
	 *        мыщи
	 * \return координата
	 */
	[[nodiscard]] const QPointF& lastLeftMousePressed() const;

	/*!
	 * \brief Установить координату, где только что была нажата кнопка мыщи
	 * \param newLastLeftMouseClick - новая координата
	 */
	void setLastLeftMousePressed(const QPointF& newLastLeftMousePressed);

	/*!
	 * \brief Получить координату где последний раз была отжата левая кнопка
	 *        мыщи
	 * \return координата
	 */
	[[nodiscard]] const QPointF& lastLeftMouseReleased() const;

	/*!
	 * \brief Установить координату, где только что была отжата кнопка мыщи
	 * \param newLastLeftMouseReleased - новая координата
	 */
	void setLastLeftMouseReleased(const QPointF& newLastLeftMouseReleased);

	/*!
	 * \brief Метод проверяет произошел ли клик левой кнопки мыщи.
	 *        Кликом считается пара действие - нажатие мыщи и не слишком
	 *	      далекое, от нажатия, отжатие мыщи
	 * \param newLeftMouseRelease - координата отжатия мыщи
	 * \warning Для правильной отработки функции надо вызвать
	 *          setLastLeftMousePressed()
	 * \return true - если произошел клик.
	 */
	[[nodiscard]] bool isLeftMouseClicked(const QPointF& newLeftMouseRelease);

	/*!
	 * \brief Перегрузка метода проверки на клик. Отличие в том, что
	 *        подставляется не вторая координата, а сверяется
	 *        m_lastLeftMousePressed и m_lastLeftMouseReleased
	 * \warning Для правильной отработки функции сначла надо вызвать
	 *          setLastLeftMousePressed(), а потом обязательно
	 *          setLastLeftMouseReleased()
	 * \return true - если произошел клик.
	 */
	[[nodiscard]] bool isLeftMouseClicked();

	/*!
	 * \brief Метод проверяет на достаточном удалении находятся ли две точки
	 *        друг от друга
	 * \param first - первая точка
	 * \param second - вторая точка
	 * \return true - если находятся на короткой дистанции
	 */
	[[nodiscard]] static bool isShortDistance(const QPointF& first,
											  const QPointF& second);

private:
	/*!
	 * \brief Координата нажатия на левую кнопку мыщи
	 */
	QPointF m_lastLeftMousePressed;

	/*!
	 * \brief Координата отжатия левой кнопки мыщи
	 */
	QPointF m_lastLeftMouseReleased;
};

#endif // CLICKTRACKER_H
