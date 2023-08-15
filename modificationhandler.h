#ifndef MODIFICATIONHANDLER_H
#define MODIFICATIONHANDLER_H

#include <QObject>

QT_BEGIN_NAMESPACE
class FigureScene;
class ClickTracker;
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
	explicit ModificationHandler(FigureScene*  parent,
								 ClickTracker* clickTracker);

	/*!
	 * \brief Основной деструктор
	 */
	~ModificationHandler() override;

	/*!
	 * \brief Применение модификаций к Фигурам по отпуску левой кнопки мыши
	 * \param sceneCoord - координата сцены, где произошел евент
	 */
	void modificateOnLeftMouseReleased(const QPointF& sceneCoord);

private:
	/*!
	 * \brief Метод убирает выделение со всех объектов сцены
	 */
	void unselectAllItems() const;

private:
	/*!
	 * \brief Указатель на Сцену
	 */
	FigureScene* m_parentScene;

	/*!
	 * \brief Указатель на класс трекающий клики кнопок
	 */
	ClickTracker* m_clickTracker;
};

#endif // MODIFICATIONHANDLER_H
