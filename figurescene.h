#ifndef FIGURESCENE_H
#define FIGURESCENE_H

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QMenu;
class Square;
class Circle;
class Triangle;
class Rectangle;
class ClickTracker;
QT_END_NAMESPACE

class FigureScene : public QGraphicsScene
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(FigureScene)

public:
	/*!
	 * \brief Основные режимы работы графической сцены
	 */
	enum Mode
	{
		Modification, /*!< Режим Модификации */
		SquareDraw,	  /*!< Режим отрисовки Квадрата */
		RectangleDraw, /*!< Режим отрисовки Прямоугольника */
		TriangleDraw, /*!< Режим отрисовки Треугольника */
		CircleDraw /*!< Режим отрисовки Круга */
	};
	Q_ENUM(Mode);

	/*!
	 * \brief Основной конструктор
	 * \param parent - указатель на родительский класс
	 */
	explicit FigureScene(QMenu* itemMenu, QObject* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~FigureScene();

	/*!
	 * \brief Вернуть режим, в котором сейчас находится сцена
	 * \return режим сцены
	 */
	Mode currentMode() const;

	/*!
	 * \brief Проверка признака нахождения сцены в режиме отрисовки треугольника
	 * \return true - если сцена находится в режиме отрисовки треугольника
	 */
	bool isTriangleMode() const;

	/*!
	 * \brief Установить текущий режим сцены
	 * \param newCurrentMode - новый режим
	 */
	void setCurrentMode(Mode newCurrentMode);

protected:
	/*!
	 * \brief Переопределнный метод Нажатия Кнопки Мыщи
	 * \param mouseEvent - указатель на событие
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

	/*!
	 * \brief Переопределнный метод Движения Мыщи
	 * \param mouseEvent - указатель на событие
	 */
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

	/*!
	 * \brief Переопределнный метод Отжатия Кнопки Мыщи
	 * \param mouseEvent - указатель на событие
	 */
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

private:
	/*!
	 * \brief Основные настройки данного класса
	 */
	void setupFigureScene();

	void onMouseLeftButtonPressed(QGraphicsSceneMouseEvent* mouseEvent);
	void onMouseLeftButtonMoved(QGraphicsSceneMouseEvent* mouseEvent);
	void onMouseLeftButtonReleased(QGraphicsSceneMouseEvent* mouseEvent);
	void onEmptyMouseMoved(QGraphicsSceneMouseEvent* mouseEvent);

private:
	/*!
	 * \brief Режим работы в котором, в данный момент времени, находится сцена
	 */
	Mode m_currentMode;

	// TODO: Сделать FigureHandler с методами типа PaintTriangle
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
	ClickTracker* m_clickHandler;
};

#endif // FIGURESCENE_H
