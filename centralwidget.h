#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QMenu;
class FigureScene;
class QToolButton;
class QButtonGroup;
class QActionGroup;
class QAbstractButton;
class FigureGraphicsView;
QT_END_NAMESPACE

class CentralWidget : public QWidget
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(CentralWidget);

public:
	/*!
	 * \brief Удаленный дефолтный конструткор
	 */
	CentralWidget() = delete;

	/*!
	 * \brief Основной конструктор
	 * \param fileMenu - указатель на меню из основного окна
	 * \param parent - указатель на родительский класс
	 */
	explicit CentralWidget(QMenu* fileMenu, QWidget* parent = nullptr);

	/*!
	 *  \brief Дефолтный деструктор
	 */
	~CentralWidget() override;

	/*!
	 * \brief Вернуть указатели на список кнопок для тулбара
	 * \return
	 */
	[[nodiscard]] QList<QAbstractButton*> buttons() const;

private:
	/*!
	 * \brief Создать и настроить все кнопки для Меню
	 */
	void setupMenuActions();

	/*!
	 * \brief Настроить основное Меню
	 */
	void setupFileMenu();

	/*!
	 * \brief Создать и настроить кнопки для ТулБара
	 */
	void setupToolBarButtons();

	/*!
	 * \brief Создать и настроить Сцену для отрисовки Фигур
	 */
	void setupScene();

	/*!
	 * \brief Создать новую кнопку для тулбара
	 * \param icon - путь до иконки для кнопки
	 * \param tipText - текст подсказки
	 * \return указатель на кнопку
	 */
	QToolButton* createButton(const QString& iconPath, const QString& tipText);

private slots:
	/*!
	 * \brief Слот, активирующийся при нажатии на одну из кнопок
	 * \param index - айди кнопки
	 */
	void buttonGroupClicked(int index);

	/*!
	 * \brief Слот, активирующийся при нажатии на кнопку меню "New"
	 */
	void newFile();

	/*!
	 * \brief Слот, активирующийся при нажатии на кнопку меню "Save As"
	 */
	void saveToFile();

	/*!
	 * \brief Слот, активирующийся при нажатии на кнопку меню "Load"
	 */
	void loadFromFile();

private:
	/*!
	 * \brief Указатель на Меню Файл
	 */
	QMenu* m_pFileMenu;

	/*!
	 * \brief Указатель на основную сцену отрисовки Фигур
	 */
	FigureScene* m_figureScene;

	/*!
	 * \brief Указатель на основное представление Сцены
	 */
	FigureGraphicsView* m_figureGraphicsView;

	/*!
	 * \brief Указатель на группу Экшенов для меню
	 */
	QActionGroup* m_menuActionsGroup;

	/*!
	 * \brief Указаетль на группу кнопок ТулБара
	 */
	QButtonGroup* m_toolBarButtonGroup;
};

#endif // CENTRALWIDGET_H
