#ifndef MODIFICATIONHANDLER_H
#define MODIFICATIONHANDLER_H

#include <QObject>

QT_BEGIN_NAMESPACE
class ClickTracker;
class FigureGraphicsView;
QT_END_NAMESPACE

/*!
 * \brief Класс прослойка для модификации объектов фигур.
 */
class ModificationHandler : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(ModificationHandler);

public:
	/*!
	 * \brief Удаленный дефолтный деструткор
	 */
	ModificationHandler() = delete;

	/*!
	 * \brief Основной конструктор
	 * \param scene - указатель на сцену
	 * \param parent - указатель на родительский класс
	 */
	explicit ModificationHandler(FigureGraphicsView* parent,
								 ClickTracker*		 clickTracker);

	/*!
	 * \brief Основной деструктор
	 */
	~ModificationHandler() override;

	/*!
	 * \brief Действия проводимые над фигурами, при нажатии на левую кнопку мыщи
	 * \param coordPress - координата, где была нажата левая кнопка мыщи
	 */
	void modificateOnLeftButtonPressed(const QPoint& coordPress);

	/*!
	 * \brief Действия проводимые над фигурами, при нажатии на левую кнопку мыщи
	 * \param coordPress - координата, где была нажата левая кнопка мыщи
	 */
	void modificateOnLeftButtonClicked(const QPoint& coordPress);

	/*!
	 * \brief Действия проводимые над фигурами, при нажатии на левую кнопку мыщи
	 *        с CTRL
	 * \param coordPress - координата, где была нажата левая кнопка мыщи
	 */
	void modificateOnLeftMouseAndCtrl(const QPoint& coordPress);

private:
	/*!
	 * \brief Метод убирает выделение со всех объектов сцены
	 */
	void unselectAllItems() const;

private:
	/*!
	 * \brief Указатель на Вьюшку сцены родителя
	 */
	FigureGraphicsView* m_parentView;

	/*!
	 * \brief Указатель на класс трекающий клики кнопок
	 */
	ClickTracker* m_clickTracker;
};

#endif // MODIFICATIONHANDLER_H
