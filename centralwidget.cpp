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
	, m_fileToSaveName{}
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

void CentralWidget::closeEvent(QCloseEvent* event)
{
	if (m_fileToSaveName.isEmpty())
	{
		saveToFile();
	}
	else
	{
		saveFile();
	}
	QWidget::closeEvent(event);
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

	// Добавляем кнопку Сохранить
	auto* saveAction = new QAction(tr("&Save"), this);
	saveAction->setShortcut(QKeySequence::Save);
	saveAction->setStatusTip(tr("Save your data in file"));
	connect(saveAction, &QAction::triggered, this, &CentralWidget::saveFile);
	m_menuActionsGroup->addAction(saveAction);

	// Добавляем кнопку Загрузить
	auto* loadAction = new QAction(tr("&Load"), this);
	loadAction->setShortcut(QKeySequence::Open);
	loadAction->setStatusTip(tr("Save your data in file"));
	connect(
		loadAction, &QAction::triggered, this, &CentralWidget::loadFromFile);
	m_menuActionsGroup->addAction(loadAction);

	// Добавляем кнопку Сохранить как
	auto* saveAsAction = new QAction(tr("&Save as..."), this);
	saveAsAction->setShortcut(QKeySequence::SaveAs);
	saveAsAction->setStatusTip(tr("Save as your data in file"));
	connect(
		saveAsAction, &QAction::triggered, this, &CentralWidget::saveToFile);
	m_menuActionsGroup->addAction(saveAsAction);

	// Добавляем кнопку выхода из приложения
	auto* exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcut(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Exit from application"));
	connect(exitAction, &QAction::triggered, this, &CentralWidget::exitFromApp);
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
	auto* modificationButton = createButton(QLatin1String("./images/plus.png"),
											tr("Modification Mode"));
	modificationButton->setChecked(true);
	m_toolBarButtonGroup->addButton(modificationButton,
									int{FigureScene::Modification});

	// Добавить кнопку отрисовки Квадрата
	m_toolBarButtonGroup->addButton(
		createButton(QLatin1String("./images/square.png"),
					 tr("Square Draw Mode")),
		int{FigureScene::SquareDraw});

	// Добавить кнопку отрисовки Прямоугольника
	m_toolBarButtonGroup->addButton(
		createButton(QLatin1String("./images/rectangle.png"),
					 tr("Rectangle Draw Mode")),
		int{FigureScene::RectangleDraw});

	// Добавить кнопку отрисовки Треугольника
	m_toolBarButtonGroup->addButton(
		createButton(QLatin1String("./images/triangle.png"),
					 tr("Triangle Draw Mode")),
		int{FigureScene::TriangleDraw});

	// Добавить кнопку отрисовки Окружности
	m_toolBarButtonGroup->addButton(
		createButton(QLatin1String("./images/circle.png"),
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

void CentralWidget::newFile()
{
	if (m_fileToSaveName.isEmpty())
	{
		saveToFile();
	}
	else
	{
		saveFile();
	}
	m_figureScene->clear();
}

void CentralWidget::saveFile()
{
	if (m_figureScene->items().empty())
	{
		return;
	}

	if (m_fileToSaveName.isEmpty())
	{
		saveToFile();
		return;
	}

	QFile	  file(m_fileToSaveName);
	QFileInfo fileInfo{m_fileToSaveName};

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
		pixMap.save(m_fileToSaveName);
	}
	else
	{
		QDataStream out(&file);
		out.setVersion(QDataStream::Qt_5_13);
		out << m_figureGraphicsView->figuresData();
	}

	file.close();
}

void CentralWidget::saveToFile()
{
	m_fileToSaveName = QFileDialog::getSaveFileName(
		this,
		tr("Save Figures data"),
		"",
		tr("Figure Designer (*.fgd);;JSON (*.json);;Picture (*.png)"));

	QFileInfo fileInfo{m_fileToSaveName};

	if (m_fileToSaveName.isEmpty())
	{
		return;
	}

	QFile file(m_fileToSaveName);
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
		m_figureScene->clearSelection();
		QPixmap pixMap = m_figureGraphicsView->grab();
		pixMap.save(m_fileToSaveName);
	}
	else
	{
		QDataStream out(&file);
		out.setVersion(QDataStream::Qt_5_13);
		out << m_figureGraphicsView->figuresData();
	}

	file.close();
}

void CentralWidget::loadFromFile()
{
	m_fileToSaveName = QFileDialog::getOpenFileName(
		this,
		tr("Open Figure Designer save"),
		"",
		tr("Figure Designer (*.fgd);;All Files (*)"));
	if (m_fileToSaveName.isEmpty())
	{
		return;
	}

	QFile	  file(m_fileToSaveName);
	QFileInfo fileInfo{m_fileToSaveName};
	if (fileInfo.suffix() != "fgd")
	{
		m_fileToSaveName.clear();
		QMessageBox::information(
			this, tr("Unable to open file"), file.errorString());
		return;
	}

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(
			this, tr("Unable to open file"), file.errorString());
		return;
	}

	QJsonDocument doc;
	QDataStream	  in(&file);
	in.setVersion(QDataStream::Qt_5_13);
	in >> doc;

	if (doc.isEmpty())
	{
		QMessageBox::information(this,
								 tr("No contacts in file"),
								 tr("The file you are attempting to open "
									"contains no contacts."));
	}
	else
	{
		m_figureScene->clear();
		m_figureGraphicsView->addedLoadedData(doc);
	}
}

void CentralWidget::exitFromApp()
{
	if (m_fileToSaveName.isEmpty())
	{
		saveToFile();
	}
	else
	{
		saveFile();
	}
	QCoreApplication::quit();
}
