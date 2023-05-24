#pragma once

#ifndef FIGURESCENE_H
#define FIGURESCENE_H

#include <QGraphicsScene>

class FigureScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /*!
     * \brief Основной конструктор
     * \param parent - указатель на родительский класс
     */
    explicit FigureScene(QObject* parent = nullptr);

protected:
    /*!
     * \brief Переопределяемый метод отрисовки заднего фона сцены
     * \param painter - указатель на отрисовщик
     * \param rect - размеры
     */
    void drawBackground(QPainter* painter, const QRectF& rect) override;

private:
    /*!
     * \brief Метод генерирующий сетку для сцены
     * \param gridVector - вектор с линиями  на заполнение одним цветом
     * \param gridVectorDark - вектор с линиями на заполнение цветом темнее
     * \param rect - размеры
     */
    void generateGrids(QVector<QLine>& gridVector,
                       QVector<QLine>& gridVectorDark,
                       const QRectF&   rect);

    /*!
     * \brief Метод устанавливает границы сцены
     * \param width - ширина
     * \param height - высота
     */
    void setSceneBoundaries(const int32_t width, const int32_t height);

private:
    /*!
     * \brief одно деление сетки
     */
    const uint8_t m_gridSize;

    /*!
     * \brief размер одно кввадрата сетки
     */
    const uint8_t m_gridSquares;
};

#endif // FIGURESCENE_H
