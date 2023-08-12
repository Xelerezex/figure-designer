#ifndef FIGURESCENE_H
#define FIGURESCENE_H

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QMenu;
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
		TriangleDraw, /*!< Режим отрисовки Триугольника */
		CircleDraw /*!< Режим отрисовки Круга */
	};

	/*!
	 * \brief Основной конструктор
	 * \param parent - указатель на родительский класс
	 */
	explicit FigureScene(QMenu* itemMenu, QObject* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~FigureScene();

private:
	/*!
	 * \brief Основные настройки данного класса
	 */
	void setupFigureScene();
};

#endif // FIGURESCENE_H
