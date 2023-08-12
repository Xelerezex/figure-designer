#include "centralwidget.h"

#include <QButtonGroup>
#include <QToolButton>
#include <QAction>

#include "figurescene.h"

CentralWidget::CentralWidget(QWidget* parent)
	: QWidget{parent}
	, m_toolBarButtonGroup{nullptr}
{
	// Создать и настроить все кнопки для тулбара
	createToolBarButtons();
}

QList<QAbstractButton*> CentralWidget::buttons() const
{
	return m_toolBarButtonGroup->buttons();
}

void CentralWidget::createToolBarButtons()
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
