#ifndef FIGUREHANDLER_H
#define FIGUREHANDLER_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QMenu;
class Square;
class Circle;
class Triangle;
class Rectangle;
class ClickTracker;
class QGraphicsItem;
class FigureGraphicsView;
QT_END_NAMESPACE

/*!
 * \brief Класс прослойка для взаимодействия с объектами фигур.
 */
class FigureHandler : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(FigureHandler);

public:
	/*!
	 * \brief Удаленный дефолтный деструткор
	 */
	FigureHandler() = delete;

	/*!
	 * \brief Основной конструктор
	 * \param fileMenu - указатель на основное Меню
	 * \param parent - указатель на родительский класс
	 */
	explicit FigureHandler(QMenu*			   fileMenu,
						   ClickTracker*	   clickTracker,
						   FigureGraphicsView* parent);

	/*!
	 * \brief Основной деструктор
	 */
	~FigureHandler() override;

	/*!
	 * \brief Создать и добавить новую фигуру Квадрата.
	 *        Также после вызова этого метода начинается отрисовка фигуры.
	 * \param itemCoord - координаты фигуры в системе кординат Элемента Сцены
	 * \param sceneCoord - координата фигуры на Сцене
	 */
	void addNewSquare(QPointF itemCoord, QPointF sceneCoord);

	/*!
	 * \brief Создать и добавить новую фигуру Прямоугольника.
	 *        Также после вызова этого метода начинается отрисовка фигуры.
	 * \param itemCoord - координаты фигуры в системе кординат Элемента Сцены
	 * \param sceneCoord - координата фигуры на Сцене
	 */
	void addNewRectangle(QPointF itemCoord, QPointF sceneCoord);

	/*!
	 * \brief Создать и добавить новую фигуру Круга.
	 *        Также после вызова этого метода начинается отрисовка фигуры.
	 * \param itemCoord - координаты фигуры в системе кординат Элемента Сцены
	 * \param sceneCoord - координата фигуры на Сцене
	 */
	void addNewCircle(QPointF itemCoord, QPointF sceneCoord);

	/*!
	 * \brief Создать и добавить новую точку для Треугольлник.
	 *        Также после вызова этого метода начинается отрисовка линии.
	 *        Если нарисована третья точка Треугольника - метод завершит
	 *        отрисовку фигуры.
	 * \param itemCoord - координаты фигуры в системе кординат Элемента Сцены
	 * \param sceneCoord - координата фигуры на Сцене
	 */
	void addNewTriangleDot(QPointF itemCoord, QPointF sceneCoord);

	/*!
	 * \brief Метод позволяющий продолжить отрисовку Квадрата
	 * \param coordinate - координаты фигуры в системе кординат Элемента Сцены
	 */
	void continueDrawingSquare(QPointF itemCoord);

	/*!
	 * \brief Метод позволяющий продолжить отрисовку Прямоугольника
	 * \param coordinate - координаты фигуры в системе кординат Элемента Сцены
	 */
	void continueDrawingRectangle(QPointF coordinate);

	/*!
	 * \brief Метод позволяющий продолжить отрисовку Круга
	 * \param coordinate - координаты фигуры в системе кординат Элемента Сцены
	 */
	void continueDrawingCircle(QPointF coordinate);

	/*!
	 * \brief Метод позволяющий продолжить отрисовку Треугольника
	 * \param coordinate - координаты фигуры в системе кординат Элемента Сцены
	 */
	void continueDrawingTriangle(QPointF coordinate);

	/*!
	 * \brief Завершить отрисовку Квадрата
	 * \param coordinate - координаты фигуры в системе кординат Элемента Сцены
	 */
	void completeSquare(QPointF coordinate);

	/*!
	 * \brief Завершить отрисовку Прямоугольника
	 * \param coordinate - координаты фигуры в системе кординат Элемента Сцены
	 */
	void completeRectangle(QPointF coordinate);

	/*!
	 * \brief Завершить отрисовку Круга
	 * \param coordinate - координаты фигуры в системе кординат Элемента Сцены
	 */
	void completeCircle(QPointF coordinate);

	/*!
	 * \brief Метод отменяет любую отрисовку Фигуры в данный момент
	 */
	void abortDrawing();

	/*!
	 * \brief Метод клонирует все выделеные на сцене Фигуры
	 */
	void cloneSelectedItems();

	/*!
	 * \brief Сериализовать в объект JSON фигуру
	 * \param item - указатель на объект
	 * \return Объект JSON формата
	 */
	QJsonObject serializeFigure(QGraphicsItem* item);

	/*!
	 * \brief Десериализовать из JSON объекта данные
	 *        и добавить фигуру на сцену, по полученным данным
	 * \param object - объект JSON
	 */
	void deserializeFigure(QJsonObject& object);

private:
	/*!
	 * \brief Данный метод позволяет удалить Треугольник со сцены,
	 *        если точки расположены слигком близко друг к другу
	 */
	void handleTriangleRemovement();

	/*!
	 * \brief Метод убирает выделение со всех объектов сцены
	 */
	void unselectAllItems() const;

private:
	/*!
	 * \brief Указатель на Меню Файл
	 */
	QMenu* m_pFileMenu;

	/*!
	 * \brief Указатель на Вьюшку сцены родителя
	 */
	FigureGraphicsView* m_parentView;

	/*!
	 * \brief Указатель на Квадрат с которым идет взаимодействие
	 */
	Square* m_currentSquare;

	/*!
	 * \brief Указатель на Прямоугольник с которым идет взаимодействие
	 */
	Rectangle* m_currentRectangle;

	/*!
	 * \brief Указатель на Круг с которым идет взаимодействие
	 */
	Circle* m_currentCircle;

	/*!
	 * \brief Указатель на Треугольника с которым идет взаимодействие
	 */
	Triangle* m_currentTriangle;

	/*!
	 * \brief Указатель на класс трекающий клики кнопок
	 */
	ClickTracker* m_clickTracker;
};

#endif // FIGUREHANDLER_H
