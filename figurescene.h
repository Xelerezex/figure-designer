#ifndef FIGURESCENE_H
#define FIGURESCENE_H

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QMenu;
class Square;
class Rectangle;
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

private:
	/*!
	 * \brief Режим работы в котором, в данный момент времени, находится сцена
	 */
	Mode m_currentMode;

	/*!
	 * \brief Указатель на Квадрат с которым идет взаимодействие
	 */
	Square* m_currentSquare;

	/*!
	 * \brief Указатель на Прямоугольник с которым идет взаимодействие
	 */
	Rectangle* m_currentRectangle;
};

#endif // FIGURESCENE_H
