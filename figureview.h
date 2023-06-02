#pragma once

#ifndef FIGUREVIEW_H
#define FIGUREVIEW_H

#include <QGraphicsView>
#include <QObject>

class FigureView : public QGraphicsView
{
public:
    /*!
     * \brief Основной конструктор
     * \param scene - указатель на сцену
     * \param parent - указатель на виджет
     */
    explicit FigureView(QGraphicsScene* scene, QWidget* parent = nullptr);

protected:
    /*!
     * \brief Переопределенные методы нажатия мыши
     * \param event - указатель на Ивент
     */
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;

    /*!
     * \brief Методы определяющие события нажатия кнопок
     * \param event - указатель на Ивент
     */
    virtual void middleMouseButtonPress(QMouseEvent* event);
    virtual void middleMouseButtonRelease(QMouseEvent* event);
    virtual void leftMouseButtonPress(QMouseEvent* event);
    virtual void leftMouseButtonRelease(QMouseEvent* event);
    virtual void rightMouseButtonPress(QMouseEvent* event);
    virtual void rightMouseButtonRelease(QMouseEvent* event);
};

#endif // FIGUREVIEW_H
