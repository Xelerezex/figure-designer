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

	/*!
	 * \brief Установить текущий режим сцены
	 * \param newCurrentMode - новый режим
	 */
	void setCurrentMode(Mode newCurrentMode);

private:
	/*!
	 * \brief Режим работы в котором, в данный момент времени, находится сцена
	 */
	Mode m_currentMode;

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
