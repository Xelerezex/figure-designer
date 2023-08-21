#include "centralwidget.h"

#include <QApplication>
#include <QButtonGroup>
#include <QGraphicsView>
#include <QFileDialog>
#include <QToolButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QAction>
#include <QMenu>

#include <QJsonDocument>

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

	// Добавляем кнопку Новый Файл
	auto* newAction = new QAction(tr("&New"), this);
	newAction->setShortcut(QKeySequence::New);
	newAction->setStatusTip(tr("Clean whole sceen"));
	connect(newAction, &QAction::triggered, this, &CentralWidget::newFile);
	m_menuActionsGroup->addAction(newAction);

	// Добавляем кнопку Сохранить как
	auto* saveAsAction = new QAction(tr("&Save as..."), this);
	saveAsAction->setShortcut(QKeySequence::SaveAs);
	saveAsAction->setStatusTip(tr("Save your data in file"));
	connect(
		saveAsAction, &QAction::triggered, this, &CentralWidget::saveToFile);
	m_menuActionsGroup->addAction(saveAsAction);

	// Добавляем кнопку выхода из приложения
	auto* exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcut(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Exit from application"));
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

#include <QDebug>
void CentralWidget::newFile()
{
	m_figureScene->clear();
}

void CentralWidget::saveToFile()
{
	QString fileName = QFileDialog::getSaveFileName(
		this,
		tr("Save Figures data"),
		"",
		tr("Figure Designer (*.fgd);;JSON (*.json);;Picture (*.png)"));

	QFileInfo fileInfo{fileName};

	qDebug() << fileInfo.baseName() << fileInfo.suffix();

	if (fileName.isEmpty())
	{
		return;
	}

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::information(
			this, tr("Unable to open file"), file.errorString());
		return;
	}

	if (fileInfo.suffix() == "json")
	{
		file.write(m_figureGraphicsView->figuresData().toJson());
	}
	else if (fileInfo.suffix() == "png")
	{
		QPixmap pixMap = m_figureGraphicsView->grab();
		pixMap.save(fileName);
	}
	else
	{
		QDataStream out(&file);
		out.setVersion(QDataStream::Qt_5_13);
		out << m_figureGraphicsView->figuresData();
	}

	file.close();
}
