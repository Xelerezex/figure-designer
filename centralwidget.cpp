#include "centralwidget.h"

#include <QButtonGroup>
#include <QGraphicsView>
#include <QToolButton>
#include <QHBoxLayout>
#include <QAction>

#include "figurescene.h"
#include "figuregraphicsview.h"

CentralWidget::CentralWidget(QWidget* parent)
	: QWidget{parent}
	, m_figureScene{nullptr}
	, m_figureGraphicsView{nullptr}
	, m_toolBarButtonGroup{nullptr}
{
	// Создать и настроить все кнопки для тулбара
	setupToolBarButtons();

	// Создать и настроить Сцену для отрисовки Фигур
	setupScene();

	// Устанавливаем имя объекта класса
	setObjectName(QLatin1String("CentralWidget"));
}

QList<QAbstractButton*> CentralWidget::buttons() const
{
	return m_toolBarButtonGroup->buttons();
}

void CentralWidget::setupToolBarButtons()
{
	m_toolBarButtonGroup = new QButtonGroup{this};
	// Позволяем зажимать только один режим
	m_toolBarButtonGroup->setExclusive(true);

	// Добавить кнопку режима Модифкации
	auto modificationButton = createButton(QLatin1String(":/images/plus.png"),
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
	// TODO: Не забыть вставить сюда Меню
	m_figureScene = new FigureScene{/*nullptr,*/ this};

	// TODO: Отнаследоваться от сцены. Либо самостоятельно задать ей флаги
	m_figureGraphicsView = new FigureGraphicsView{m_figureScene};

	// Создание основного лейаута со Сценой
	auto* mainLayout = new QHBoxLayout;
	mainLayout->addWidget(m_figureGraphicsView);

	setLayout(mainLayout);
}

QToolButton* CentralWidget::createButton(const QString& iconPath,
										 const QString& tipText)
{
	const int buttonSize{65};

	auto	  button = new QToolButton{this};
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
}
