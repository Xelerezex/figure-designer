#ifndef FIGURESCENE_H
#define FIGURESCENE_H

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

/*!
 * \brief Класс Сцены
 */
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

private:
	/*!
	 * \brief Основные настройки данного класса
	 */
	void setupFigureScene();
};

#endif // FIGURESCENE_H
