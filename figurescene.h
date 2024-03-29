#ifndef FIGURESCENE_H
#define FIGURESCENE_H

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QMenu;
class ClickTracker;
class CentralWidget;
class ModificationHandler;
QT_END_NAMESPACE

/*!
 * \brief Класс Сцены
 */
class FigureScene : public QGraphicsScene
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(FigureScene)
	// Разрешает центральному виджету изменять режим работы графической сцены
	friend CentralWidget;

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
	 * \brief Дефолтный удаленный конструктор
	 */
	FigureScene() = delete;

	/*!
	 * \brief Основной конструктор
	 * \param itemMenu - указатель на меню из центрального виджета
	 * \param parent - указатель на родительский класс
	 */
	explicit FigureScene(QMenu* itemMenu, QObject* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~FigureScene() override;

	/*!
	 * \brief Вернуть режим, в котором сейчас находится сцена
	 * \return режим сцены
	 */
	[[nodiscard]] Mode currentMode() const;

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

	/*!
	 * \brief Переопределнный метод Отжатия кнопки
	 * \param event - указатель на событие
	 */
	void keyReleaseEvent(QKeyEvent* event) override;

private:
	/*!
	 * \brief Основные настройки данного класса
	 */
	void setupFigureScene();

	/*!
	 * \brief Установить текущий режим сцены
	 * \param newCurrentMode - новый режим
	 */
	void setCurrentMode(Mode newCurrentMode);

	/*!
	 * \brief Метод, вызываемый при нажатии на левую кнопку мыши
	 * \param mouseEvent - событие мыщи
	 */
	void onLeftMousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при движении мыши
	 * \param mouseEvent - событие мыщи
	 */
	void onLeftMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при разжатии левой кнопки мыщи
	 * \param mouseEvent - событие мыщи
	 */
	void onLeftMouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при нажатии на правую кнопку мыши
	 * \param mouseEvent - событие мыщи
	 */
	void onRightMousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);

	/*!
	 * \brief Метод, вызываемый при движении с зажатой правой кнопокой мыши
	 * \param mouseEvent - событие мыщи
	 */
	void onRightMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);

	/*!
	 * \brief Метод для удаления всех выделенных фигур
	 */
	void handleSelectedDelete();

private:
	/*!
	 * \brief Режим работы в котором, в данный момент времени, находится сцена
	 */
	Mode m_currentMode;

	/*!
	 * \brief Указатель на Меню Файл
	 */
	QMenu* m_pFileMenu;

	/*!
	 * \brief Указатель на класс трекающий клики кнопок
	 */
	ClickTracker* m_clickTracker;

	/*!
	 * \brief Указатель на обработчик модификации объектов фигур
	 */
	ModificationHandler* m_modificationHandler;
};

#endif // FIGURESCENE_H
