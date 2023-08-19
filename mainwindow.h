#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class CentralWidget;
class ToolBar;
QT_END_NAMESPACE

/*!
 * \brief Класс основного окна
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(MainWindow);

public:
	/*!
	 * \brief Конструктор
	 * \param parent - указатель на родительский виджет
	 */
	explicit MainWindow(QWidget* parent = nullptr);

	/*!
	 * \brief Основной Деструктор
	 */
	~MainWindow() override;

private:
	/*!
	 * \brief Настроить основное окно
	 */
	void setupMainWindow();

	/*!
	 * \brief Создать и настроить тулбар на главном окне
	 */
	void setupToolBar();

	/*!
	 * \brief Создать и настроить меню на главном окне
	 */
	void setupMenu();

	/*!
	 * \brief Создать и настроить центральный виджет
	 */
	void setupCentralWidget();

	/*!
	 * \brief Передать указатели на кнопки из центрального виджета в тулбар
	 */
	void setupToolBarButtons();

	/*!
	 * \brief Переопределенная функция вызывающаяся при закрытии окна
	 * \param event - указатель на событие закрытия
	 */
	void closeEvent(QCloseEvent* event) override;

	/*!
	 * \brief Записать позиции основного окна в файл настроек
	 */
	void writeState();

	/*!
	 * \brief Прочитать позиции основного окна из файла настроек
	 */
	void readState();

private:
	/*!
	 * \brief Указатель на основной виджет
	 */
	CentralWidget* m_pCentralWidget;

	/*!
	 * \brief Указатель на основной тулбар
	 */
	QToolBar* m_pToolBar;

	/*!
	 * \brief Указатель на основное Меню
	 */
	QMenu* m_pMenu;
};

#endif // MAINWINDOW_H
