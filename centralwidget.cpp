#include "centralwidget.h"

#include <QButtonGroup>
#include <QGraphicsView>
#include <QToolButton>
#include <QHBoxLayout>
#include <QAction>

#include "figurescene.h"

CentralWidget::CentralWidget(QWidget* parent)
	: QWidget{parent}
	, m_toolBarButtonGroup{nullptr}
	, m_figureScene{nullptr}
	, m_graphicsView{nullptr}
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
	m_toolBarButtonGroup->addButton(
		createButton(QLatin1String(":/images/plus.png"),
					 tr("Modification Mode")),
		int{FigureScene::Modification});

	// Добавить кнопку отрисовки Квадрата
	m_toolBarButtonGroup->addButton(
		createButton(QLatin1String(":/images/square.png"),
					 tr("Square Draw Mode")),
		int{FigureScene::SquareDraw});
}

void CentralWidget::setupScene()
{
	// TODO: Не забыть вставить сюда Меню
	m_figureScene = new FigureScene{nullptr, this};

	m_graphicsView = new QGraphicsView{m_figureScene};

	// Создание основного лейаута со Сценой
	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addWidget(m_graphicsView);

	setLayout(mainLayout);
}

QToolButton* CentralWidget::createButton(const QString& iconPath,
										 const QString& tipText)
{
	auto button = new QToolButton{this};
	button->setToolTip(tipText);
	button->setCheckable(true);
	button->setIcon(QIcon(QPixmap(iconPath)));
	button->setIconSize(QSize(65, 65));

	return button;
}
