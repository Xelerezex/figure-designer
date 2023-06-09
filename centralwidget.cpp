#include "centralwidget.h"

#include "figurescene.h"
#include "figureview.h"
#include "rectangle.h"
#include "rectanglesceneobject.h"
#include "square.h"
#include "squaresceneobject.h"
#include "triangle.h"
#include "trianglesceneobject.h"
#include "circle.h"
#include "circlesceneobject.h"

#include <QAction>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QShortcut>

CentralWidget::CentralWidget(QWidget* parent)
    : QWidget(parent)
{
    // Настрока этого (центрального) виджета
    setupCentralWidget();

    // Создание и настройка кнопок для тулбара
    setupActions();

    // Создание и настройка виджета сцены
    setupScene();

    // Создание и настройка шорткатов
    setupShortcuts();

    // Создание и настройка основного лейаута
    setupMainLayout();

    // Соединения Signal/Slot:
    setupSignalSlotsConnection();
}

CentralWidget::~CentralWidget()
{
}

void CentralWidget::setupCentralWidget()
{
    setObjectName(QStringLiteral("CentralWidget"));
}

void CentralWidget::setupActions()
{
    m_pCircleAction	   = createAction(QStringLiteral("Circle"),
                                      QStringLiteral(":/images/circle.png"));
    m_pSquareAction	   = createAction(QStringLiteral("Square"),
                                      QStringLiteral(":/images/square.png"));
    m_pRectangleAction = createAction(QStringLiteral("Rectangle"),
                                      QStringLiteral(":/images/rectangle.png"));
    m_pTriangleAction  = createAction(QStringLiteral("Triangle"),
                                      QStringLiteral(":/images/triangle.png"));
}

void CentralWidget::setupScene()
{
    m_scene = new FigureScene(this);
    m_view	= new FigureView(m_scene, this);
    m_view->setScene(m_scene);
}

void CentralWidget::setupShortcuts()
{
    QShortcut* ctrlZ = new QShortcut{QKeySequence{"Ctrl+Z"}, this};
    connect(ctrlZ, &QShortcut::activated, this, &CentralWidget::onCtrlZ);
}

void CentralWidget::setupMainLayout()
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_view);
    setLayout(mainLayout);
}

QAction* CentralWidget::createAction(const QString& name,
                                     const QString& iconPath)
{
    // Создаем иконку
    const QIcon icon = QPixmap(iconPath, nullptr, Qt::AutoColor);

    // Создаем и настраиваем кнопку
    QAction* actionPointer = new QAction(name, this);

    Q_ASSERT_X(
        actionPointer, "CentralWidget::createAction", "Action not created");

    actionPointer->setIcon(icon);
    actionPointer->setObjectName(name);
    actionPointer->setData(true);

    return actionPointer;
}

void CentralWidget::setupSignalSlotsConnection()
{
    connect(m_pCircleAction,
            &QAction::triggered,
            this,
            &CentralWidget::onCircleAction);

    connect(m_pSquareAction,
            &QAction::triggered,
            this,
            &CentralWidget::onSquareAction);

    connect(m_pRectangleAction,
            &QAction::triggered,
            this,
            &CentralWidget::onRectangleAction);

    connect(m_pTriangleAction,
            &QAction::triggered,
            this,
            &CentralWidget::onTriangleAction);
}

QList<QAction*> CentralWidget::actions()
{
    return createListActions();
}

QList<QAction*> CentralWidget::createListActions()
{
    return QList<QAction*>{m_pCircleAction,
                           createSeparator(),
                           m_pSquareAction,
                           createSeparator(),
                           m_pRectangleAction,
                           createSeparator(),
                           m_pTriangleAction,
                           createSeparator()};
}

QAction* CentralWidget::createSeparator()
{
    QAction* separator = new QAction(this);
    separator->setSeparator(true);
    return separator;
}

void CentralWidget::onCircleAction()
{
    qDebug("Pressed Circle");

    auto circle = QSharedPointer<CircleSceneObject>::create(
        static_cast<unsigned int>(m_sceneObjects.size()), new Circle{25});

    m_scene->addItem(circle.get());

    m_sceneObjects.append(circle);
}

void CentralWidget::onSquareAction()
{
    qDebug("Pressed Square");

    // square{};

    auto square = QSharedPointer<SquareSceneObject>::create(
        static_cast<unsigned int>(m_sceneObjects.size()), new Square{50});

    m_scene->addItem(square.get());

    m_sceneObjects.append(square);
}

void CentralWidget::onRectangleAction()
{
    qDebug("Pressed Rectangle");

    auto rectangle = QSharedPointer<RectangleSceneObject>::create(
        static_cast<unsigned int>(m_sceneObjects.size()),
        new Rectangle{100, 50});

    m_scene->addItem(rectangle.get());

    m_sceneObjects.append(rectangle);
}

void CentralWidget::onTriangleAction()
{
    qDebug("Pressed Triangle");

    auto triangle = QSharedPointer<TriangleSceneObject>::create(
        static_cast<unsigned int>(m_sceneObjects.size()),
        new Triangle{Point{0, 50}, Point{-70, -25}, Point{70, -25}});

    m_scene->addItem(triangle.get());

    m_sceneObjects.append(triangle);
}

void CentralWidget::onCtrlZ()
{
    if (m_sceneObjects.empty())
    {
        return;
    }

    auto figurePointer = m_sceneObjects.top();
    m_scene->removeItem(figurePointer.get());

    m_sceneObjects.pop();
}
