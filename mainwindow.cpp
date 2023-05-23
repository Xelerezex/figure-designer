#include "mainwindow.h"

#include "centralwidget.h"

#include <QApplication>
#include <QSettings>
#include <QToolBar>

/*!
 * \brief Конструктор
 * \param parent - указатель на родительский виджет
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Настроить основное окно
    setupMainWindow();

    // Создать и настроить тулбар на главном окне
    setupToolBar();

    // Создать и настроить центральный виджет
    setupCentralWidget();

    // Передать указатели на кнопки из центрального виджета в тулбар
    setupToolBarButtons();

    // Прочитать позиции основного окна из файла настроек
    readState();
}

/*!
 * \brief Деструктор
 */
MainWindow::~MainWindow()
{
}

/*!
 * \brief Настроить основное окно
 */
void MainWindow::setupMainWindow()
{
    // Устанавливаем название организации
    QCoreApplication::setOrganizationName(tr("Top Systems"));

    // Устанавливаем название приложения
    QCoreApplication::setApplicationName(QLatin1String("Figure Designer"));

    // Устанавливаем имя объекта класса
    setObjectName(QLatin1String("MainWindow"));
}

/*!
 * \brief Создать и настроить тулбар на главном окне
 */
void MainWindow::setupToolBar()
{
    // Создаем объект тулбар и задаем ему имя
    m_pToolBar = new QToolBar(this);
    m_pToolBar->setObjectName(QLatin1String("ToolBar"));

    // Запрещает скрытие тулбара при нажатии на правую кнопку мыши
    m_pToolBar->setContextMenuPolicy(Qt::PreventContextMenu);

    // Добавим тулбар на основное окно
    addToolBar(m_pToolBar);
}

/*!
 * \brief Создать и настроить центральный виджет
 */
void MainWindow::setupCentralWidget()
{
    // Создадим и настроем центральный виджет
    m_pCentralWidget = new CentralWidget(this);

    // Добавим центральный виджет на основное окно
    setCentralWidget(m_pCentralWidget);
}

/*!
 * \brief Передать указатели на кнопки из центрального виджета в тулбар
 */
void MainWindow::setupToolBarButtons()
{
    m_pToolBar->addActions(m_pCentralWidget->actions());
}

/*!
 * \brief Переопределенная функция вызывающаяся при закрытии окна
 * \param event - указатель на событие закрытия
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    // Записать позиции основного окна в файл настроек
    writeState();

    // Вызвать базовое событие закрытия
    QMainWindow::closeEvent(event);
}

/*!
 * \brief Записать позиции основного окна в файл настроек
 */
void MainWindow::writeState()
{
    // Инициируем настройку в файл
    QSettings settings(QLatin1String("settings.conf"), QSettings::IniFormat);
    settings.beginGroup(objectName());

    // Заприсываем в файл настроек геометрию и положение окна
    settings.setValue(QLatin1String("geometry"), saveGeometry());
    settings.setValue(QLatin1String("state"), saveState());
    settings.setValue(QLatin1String("maximized"), isMaximized());

    // Если окно не максимального размера запишем позицию и размер
    if (!isMaximized())
    {
        settings.setValue(QLatin1String("position"), pos());
        settings.setValue(QLatin1String("size"), size());
    }
    settings.endGroup();

    // Запускаем запись положений в центральном виджете
    // m_pCentralWidget->writeState();
}

/*!
 * \brief Прочитать позиции основного окна из файла настроек
 */
void MainWindow::readState()
{
    // Инициируем настройку из файла
    QSettings settings(QLatin1String("settings.conf"), QSettings::IniFormat);
    settings.beginGroup(objectName());

    // Восстанавливаем настройку  геометрию и положение окна
    restoreGeometry(settings.value(QLatin1String("geometry"), saveGeometry()).toByteArray());
    restoreState(settings.value(QLatin1String("state"), saveState()).toByteArray());
    move(settings.value(QLatin1String("position"), pos()).toPoint());
    resize(settings.value(QLatin1String("size"), size()).toSize());

    // Если окно максимального размера - устанавливаем его максимальные значения
    if (settings.value(QLatin1String("maximized"), isMaximized()).toBool())
    {
        showMaximized();
    }
    settings.endGroup();

    // Запускаем загрузку положений в центральном виджете
    // m_pCentralWidget->readState();
}
