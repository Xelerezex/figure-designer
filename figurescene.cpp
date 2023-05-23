#include "figurescene.h"

#include <QPainter>

FigureScene::FigureScene(QObject* parent)
    : QGraphicsScene(parent)
    , m_gridSize{20}
    , m_gridSquares{5}
{
    // Устанавливаем цвет кисти для фона
    setBackgroundBrush(QColor(3750201));

    // Устанавливаем границы сцены
    setSceneBoundaries(64'000, 64'000);
}

void FigureScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    QGraphicsScene::drawBackground(painter, rect);

    QPen ppLight(QColor(3092271));
    ppLight.setWidth(1);

    QPen ppDark(QColor(2697513));
    ppDark.setWidth(2);

    QVector<QLine> gridVector;
    QVector<QLine> gridVectorDark;

    generateGrids(gridVector, gridVectorDark, rect);

    painter->setPen(ppLight);
    painter->drawLines(gridVector);

    painter->setPen(ppDark);
    painter->drawLines(gridVectorDark);
}

void FigureScene::generateGrids(QVector<QLine>& gridVector,
                                QVector<QLine>& gridVectorDark,
                                const QRectF&	rect)
{
    int64_t left   = static_cast<int64_t>(rect.left());
    int64_t right  = static_cast<int64_t>(rect.right());
    int64_t top	   = static_cast<int64_t>(rect.top());
    int64_t bottom = static_cast<int64_t>(rect.bottom());

    int64_t first_left = left - (left % m_gridSize);
    int64_t first_top  = top - (top % m_gridSize);

    // Заполнить вектор горизонтальными линиями:
    for (int64_t x = first_left; x < right; x += m_gridSize)
    {
        if (x % (m_gridSize * m_gridSquares) != 0)
        {
            gridVector.push_back(QLine(x, top, x, bottom));
        }
        else
        {
            gridVectorDark.push_back(QLine(x, top, x, bottom));
        }
    }

    // Заполнить вектор вертикальными линиями:
    for (int64_t y = first_top; y < bottom; y += m_gridSize)
    {
        if (y % (m_gridSize * m_gridSquares) != 0)
        {
            gridVector.push_back(QLine(left, y, right, y));
        }
        else
        {
            gridVectorDark.push_back(QLine(left, y, right, y));
        }
    }
}

void FigureScene::setSceneBoundaries(const int32_t width, const int32_t height)
{
    setSceneRect(-(width / 2), -(height / 2), width, height);
}
