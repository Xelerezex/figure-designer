#ifndef FIGURESCENE_H
#define FIGURESCENE_H

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QMenu;
class FigureHandler;
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
	// TODO: Не забыть про itemMenu
	explicit FigureScene(/*QMenu* itemMenu, */ QObject* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~FigureScene() override;

	/*!
	 * \brief Вернуть режим, в котором сейчас находится сцена
	 * \return режим сцены
	 */
	[[nodiscard]] Mode currentMode() const;

	/*!
	 * \brief Проверка признака нахождения сцены в режиме отрисовки треугольника
	 * \return true - если сцена находится в режиме отрисовки треугольника
	 */
	[[nodiscard]] bool isTriangleMode() const;

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

	/*!
	 * \brief Указатель на обработчик взаимодействий с Фигурами
	 */
	FigureHandler* m_figureHandler;
};

#endif // FIGURESCENE_H
