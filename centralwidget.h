#pragma once

#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QStack>

class QAction;
class FigureScene;
class FigureView;
class SceneObject;

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Основной конструктор
     * \param parent - указатель на родительский класс
     */
    CentralWidget(QWidget* parent = nullptr);

    /*!
     * \brief Основной деструктор
     */
    ~CentralWidget();

    /*!
     * \brief Вернуть лист указателей на кнопки тулбара
     * \return лист с указателями
     */
    QList<QAction*> actions();

private:
    /*************************************************/
    /*      Методы относящиеся к работе с GUI        */
    /*************************************************/
    /*!
     * \brief Настрока этого (центрального) виджета
     */
    void setupCentralWidget();

    /*!
     * \brief Создать и настроить все кнопки тулбара
     */
    void setupActions();

    /*!
     * \brief Создание и настройка виджета сцены
     */
    void setupScene();

    /*!
     * \brief Создание и настройка шорткатов
     */
    void setupShortcuts();

    /*!
     * \brief Создание и настройка основного лейаута
     */
    void setupMainLayout();

    /*!
     * \brief Создать и настроить кнопку подключения
     * \return указатель на Action
     */
    QAction* createAction(const QString& name, const QString& iconPath);

    /*!
     * \brief Функция настраивает соединения Signal/Slots
     */
    void setupSignalSlotsConnection();

    /*!
     * \brief Создать лист указателей на кнопки тулбара
     * \return лист с указателями
     */
    QList<QAction*> createListActions();

    /*!
     * \brief Создать сепаратор для тулбара
     * \return указатель на генератор
     */
    QAction* createSeparator();

private slots:
    /*!
     * \brief Слот, обрабатывающая логику кнопки круга
     */
    void onCircleAction();

    /*!
     * \brief Слот, обрабатывающая логику кнопки квадрата
     */
    void onSquareAction();

    /*!
     * \brief Слот, обрабатывающая логику кнопки прямоугольника
     */
    void onRectangleAction();

    /*!
     * \brief Слот, обрабатывающая логику кнопки треугольника
     */
    void onTriangleAction();

    /*!
     * \brief Слот, обрабатывающая логику нажатия сочетания Ctrl+Z
     */
    void onCtrlZ();

private:
    /*!
     * \brief Указатель на кнопку отрисовки круга
     */
    QAction* m_pCircleAction;

    /*!
     * \brief Указатель на кнопку отрисовки квадрата
     */
    QAction* m_pSquareAction;

    /*!
     * \brief Указатель на кнопку отрисовки прямоугольника
     */
    QAction* m_pRectangleAction;

    /*!
     * \brief Указатель на кнопку отрисовки треугольника
     */
    QAction* m_pTriangleAction;

    /*!
     * \brief Указатель на виджет сцены
     */
    FigureScene* m_scene;

    /*!
     * \brief Указатель на отображение сцены
     */
    FigureView* m_view;

    /*!
     * \brief контейнер для всех объектов сцены
     */
    QStack<QSharedPointer<SceneObject>> m_sceneObjects;
};

#endif
