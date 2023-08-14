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
	[[nodiscard]] QPointF lastLeftMouseClick() const;

	/*!
	 * \brief Установить координату, где только что была нажата кнопка мыщи
	 * \param newLastLeftMouseClick - новая координата
	 */
	void setLastLeftMousePressed(QPointF newLastLeftMouseClick);

	/*!
	 * \brief Метод проверяет не слишком ли далеко была отжата кнопка мыщи
	 * \param newLeftMouseRelease - координата отжатия мыщи
	 * \return true - если не очень далеко
	 */
	bool isDistClickReleaseLeftMouseOk(QPointF newLeftMouseRelease);

private:
	/*!
	 * \brief Кооридната нажатия на левую кнопку мыщи
	 */
	QPointF m_lastLeftMouseClick;
};

#endif // CLICKTRACKER_H
