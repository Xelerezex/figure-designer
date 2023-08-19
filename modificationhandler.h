#ifndef MODIFICATIONHANDLER_H
#define MODIFICATIONHANDLER_H

#include <QObject>

QT_BEGIN_NAMESPACE
class FigureScene;
class ClickTracker;
class QGraphicsItem;
class SelectionRectangle;
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
	 * \brief Метод проверяет, есть ли по данным координатам какой-то объект
	 * \param sceneCoord - координаты сцены
	 * \return true - если сцена не пуста и объект есть
	 */
	[[nodiscard]] bool isOnFigure(const QPointF& sceneCoord) const;

	/*!
	 * \brief Применение модификаций к Фигурам по нажатию левой кнопки мыши
	 * \param sceneCoord - координата сцены, где произошел евент
	 */
	void modificateOnLeftMousePressed(const QPointF& sceneCoord);

	/*!
	 * \brief Применение модификаций к Фигурам по отпуску левой кнопки мыши
	 * \param sceneCoord - координата сцены, где произошел евент
	 */
	void modificateOnLeftMouseReleased(const QPointF& sceneCoord);

	/*!
	 * \brief Выделить все элементы сцены, переданные в параметр
	 * \param list - элементы на выделение
	 */
	void selectAllItemsInList(const QList<QGraphicsItem*>& list);

	/*!
	 * \brief Метод убирает выделение со всех объектов сцены
	 */
	void unselectAllItems() const;

	/*!
	 * \brief Метод начинает отрисовку прямоугольника для выбора фигур
	 * \param sceneCoord - координата сцены, где произошел евент
	 */
	void addNewSelectionRectangle(const QPointF& sceneCoord);

	/*!
	 * \brief Метод продолжает отрисовку прямоугольника для выбора фигур
	 * \param sceneCoord - координата сцены, где произошел евент
	 */
	void continueDrawingSelectionRectangle(const QPointF& sceneCoord);

	/*!
	 * \brief Метод продолжает отрисовку прямоугольника для выбора фигур
	 * \param sceneCoord - координата сцены, где произошел евент
	 */
	void completeDrawingSelectionRectangle(const QPointF& sceneCoord);

	/*!
	 * \brief Метод обновляет все выделенные отрисованные фигуры
	 */
	void updateSelectedItems() const;

	/*!
	 * \brief Начать вращение
	 * \param sceneCoord - координата сцены, где произошел евент
	 */
	void startRotation(const QPoint& sceneCoord);

	/*!
	 * \brief продолжать вращение
	 * \param sceneCoord - координата сцены, где произошел евент
	 */
	void continueRotation(const QPointF &sceneCoord);

	/*!
	 * \brief Получить объединеный прямоугольник, составленный из выделенных
	 *        фигур
	 * \return прямоугольник
	 */
	[[nodiscard]] QRectF getUnitedSelectedBoundingRect() const;

	/*!
	 * \brief Получить центр из объединенного прямоугольника
	 * \return точка
	 */
	[[nodiscard]] QPointF getUnitedSelectedCenter() const;

private:
	/*!
	 * \brief Указатель на Сцену
	 */
	FigureScene* m_parentScene;

	/*!
	 * \brief Указатель на класс трекающий клики кнопок
	 */
	ClickTracker* m_clickTracker;

	/*!
	 * \brief Указатель на класс прямоугольника выделения
	 */
	SelectionRectangle* m_selectionRect;
};

#endif // MODIFICATIONHANDLER_H
