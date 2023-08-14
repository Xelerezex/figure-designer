#ifndef FIGUREGRAPHICSVIEW_H
#define FIGUREGRAPHICSVIEW_H

#include <QGraphicsView>

class FigureGraphicsView : public QGraphicsView
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(FigureGraphicsView)

public:
	/*!
	 * \brief Дефолтный удаленный конструктор
	 */
	FigureGraphicsView() = delete;

	/*!
	 * \brief Основной конструктор
	 * \param scene - указатель на сцену
	 * \param parent - указатель на родительский виджет
	 */
	explicit FigureGraphicsView(QGraphicsScene* scene,
								QWidget*		parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~FigureGraphicsView() override;

private:
	/*!
	 * \brief Метод настраивает этот объект Вью
	 */
	void setupFigureGraphicsView();
};

#endif // FIGUREGRAPHICSVIEW_H
