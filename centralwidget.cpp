#include "centralwidget.h"

#include <QApplication>
#include <QButtonGroup>
#include <QGraphicsView>
#include <QToolButton>
#include <QHBoxLayout>
#include <QAction>
#include <QMenu>

#include "figurescene.h"
#include "figuregraphicsview.h"

CentralWidget::CentralWidget(QMenu* fileMenu, QWidget* parent)
	: QWidget{parent}
	, m_pFileMenu{fileMenu}
	, m_figureScene{nullptr}
	, m_figureGraphicsView{nullptr}
	, m_menuActionsGroup{nullptr}
	, m_toolBarButtonGroup{nullptr}
{
	// Создать и настроить все кнопки для тулбара
	setupToolBarButtons();

	// Создать и настроить все кнопки для Меню
	setupFileMenu();

	// Создать и настроить Сцену для отрисовки Фигур
	setupScene();

	// Устанавливаем имя объекта класса
	setObjectName(QLatin1String("CentralWidget"));
}

CentralWidget::~CentralWidget()
{
}

QList<QAbstractButton*> CentralWidget::buttons() const
{
	return m_toolBarButtonGroup->buttons();
}

void CentralWidget::setupMenuActions()
{
	m_menuActionsGroup = new QActionGroup{this};
	m_menuActionsGroup->setExclusive(false);

	// Добавляем кнопку выхода из приложения
	auto* exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcut(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Exit from application"));
	// FIXME: Закрывает только виджет
	connect(exitAction, &QAction::triggered, this, &QCoreApplication::quit);
	m_menuActionsGroup->addAction(exitAction);
}

void CentralWidget::setupFileMenu()
{
	setupMenuActions();

	m_pFileMenu->addActions(m_menuActionsGroup->actions());
}

void CentralWidget::setupToolBarButtons()
{
	m_toolBarButtonGroup = new QButtonGroup{this};
	// Позволяем зажимать только один режим
	m_toolBarButtonGroup->setExclusive(true);

	// Добавить кнопку режима Модифкации
	auto* modificationButton = createButton(QLatin1String(":/images/plus.png"),
											tr("Modification Mode"));
	modificationButton->setChecked(true);
	m_toolBarButtonGroup->addButton(modificationButton,
									int{FigureScene::Modification});

	// Добавить кнопку отрисовки Квадрата
	m_toolBarButtonGroup->addButton(
		createButton(QLatin1String(":/images/square.png"),
					 tr("Square Draw Mode")),
		int{FigureScene::SquareDraw});

	// Добавить кнопку отрисовки Прямоугольника
	m_toolBarButtonGroup->addButton(
		createButton(QLatin1String(":/images/rectangle.png"),
					 tr("Rectangle Draw Mode")),
		int{FigureScene::RectangleDraw});

	// Добавить кнопку отрисовки Треугольника
	m_toolBarButtonGroup->addButton(
		createButton(QLatin1String(":/images/triangle.png"),
					 tr("Triangle Draw Mode")),
		int{FigureScene::TriangleDraw});

	// Добавить кнопку отрисовки Окружности
	m_toolBarButtonGroup->addButton(
		createButton(QLatin1String(":/images/circle.png"),
					 tr("Circle Draw Mode")),
		int{FigureScene::CircleDraw});

	connect(m_toolBarButtonGroup,
			QOverload<int>::of(&QButtonGroup::buttonClicked),
			this,
			&CentralWidget::buttonGroupClicked);
}

void CentralWidget::setupScene()
{
	m_figureScene = new FigureScene{m_pFileMenu, this};

	m_figureGraphicsView
		= new FigureGraphicsView{m_pFileMenu, m_figureScene, this};

	// Создание основного лейаута со Сценой
	auto* mainLayout = new QHBoxLayout;
	mainLayout->addWidget(m_figureGraphicsView);

	setLayout(mainLayout);
}

QToolButton* CentralWidget::createButton(const QString& iconPath,
										 const QString& tipText)
{
	const int buttonSize{65};

	auto*	  button = new QToolButton{this};
	button->setToolTip(tipText);
	button->setCheckable(true);
	button->setIcon(QIcon(QPixmap(iconPath)));
	button->setIconSize(QSize(buttonSize, buttonSize));

	return button;
}

void CentralWidget::buttonGroupClicked(int index)
{
	m_figureGraphicsView->setCurrentMode(
		static_cast<FigureGraphicsView::Mode>(index));
	m_figureScene->setCurrentMode(static_cast<FigureScene::Mode>(index));
}
