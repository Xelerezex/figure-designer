#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class CentralWidget;
class ToolBar;

/*!
 * \brief Класс основного окна
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // Конструктор
    MainWindow(QWidget *parent = nullptr);

    // Деструктор
    ~MainWindow();

private:
    // Настроить основное окно
    void setupMainWindow();

    // Создать и настроить тулбар на главном окне
    void setupToolBar();

    // Создать и настроить центральный виджет
    void setupCentralWidget();

    // Передать указатели на кнопки из центрального виджета в тулбар
    void setupToolBarButtons();

    // Переопределенная функция вызывающаяся при закрытии окна
    void closeEvent(QCloseEvent *event) override;

    // Записать позиции основного окна в файл настроек
    void writeState();

    // Прочитать позиции основного окна из файла настроек
    void readState();

private:
    // Указатель на основной виджет
    CentralWidget* m_pCentralWidget;

    // Указатель на тулбар
    QToolBar* m_pToolBar;
};

#endif
