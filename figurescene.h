#ifndef FIGURESCENE_H
#define FIGURESCENE_H

#include <QGraphicsScene>

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
	explicit FigureScene(QObject* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~FigureScene();
};

#endif // FIGURESCENE_H
