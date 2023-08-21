#include "deserializefromjson.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

#include "startdrawing.h"
#include "completedrawing.h"

#include <QRegularExpressionMatch>

DeserializeFromJson::DeserializeFromJson(QJsonObject* jsonObject)
	: m_jsonObject{jsonObject}
{
}

void DeserializeFromJson::act(Circle* circle)
{
	// Получаем координаты центра в координатах фигуры
	QPointF center = toQPointF(m_jsonObject->value("Center").toString());
	// Получаем координаты второй точки в координатах фигуры
	QPointF destination
		= toQPointF(m_jsonObject->value("Destination").toString());
	// Получаем координаты фигуры в координатах сцены
	QPointF postition = toQPointF(m_jsonObject->value("Position").toString());
	// Получаем угол поворота фигуры
	qreal angle = m_jsonObject->value("Rotation").toDouble();
	// Высчитываем матрицу трансформации фигуры
	QTransform transform = toQTransform(postition, angle);

	// Отрисовывваем новый объект
	circle->act(StartDrawing{center, postition});
	circle->act(CompleteDrawing{destination});
	// Задаем новому объекту матрицу трансформации
	circle->setPos(transform.map(postition));
	circle->setRotation(angle);
}

void DeserializeFromJson::act(Square* square)
{
	// Получаем координаты центра в координатах фигуры
	QPointF center = toQPointF(m_jsonObject->value("Center").toString());
	// Получаем координаты второй точки в координатах фигуры
	QPointF destination
		= toQPointF(m_jsonObject->value("Destination").toString());
	// Получаем координаты фигуры в координатах сцены
	QPointF postition = toQPointF(m_jsonObject->value("Position").toString());
	// Получаем угол поворота фигуры
	qreal angle = m_jsonObject->value("Rotation").toDouble();
	// Высчитываем матрицу трансформации фигуры
	QTransform transform = toQTransform(postition, angle);

	// Отрисовывваем новый объект
	square->act(StartDrawing{center, postition});
	square->act(CompleteDrawing{destination});
	// Задаем новому объекту матрицу трансформации
	square->setPos(transform.map(postition));
	square->setRotation(angle);
}

void DeserializeFromJson::act(Triangle* triangle)
{
	// Получаем координаты первой точки точки в координатах фигуры
	QPointF firstDot = toQPointF(m_jsonObject->value("FirstDot").toString());
	// Получаем координаты первой точки точки в координатах фигуры
	QPointF secondDot = toQPointF(m_jsonObject->value("SecondDot").toString());
	// Получаем координаты первой точки точки в координатах фигуры
	QPointF thirdDot = toQPointF(m_jsonObject->value("ThirdDot").toString());

	// Получаем координаты фигуры в координатах сцены
	QPointF postition = toQPointF(m_jsonObject->value("Position").toString());
	// Получаем угол поворота фигуры
	qreal angle = m_jsonObject->value("Rotation").toDouble();
	// Высчитываем матрицу трансформации фигуры
	QTransform transform = toQTransform(postition, angle);

	// Отрисовывваем новый объект
	triangle->act(StartDrawing{firstDot, postition});
	triangle->act(CompleteDrawing{secondDot});
	triangle->act(CompleteDrawing{thirdDot});
	// Задаем новому объекту матрицу трансформации
	triangle->setPos(transform.map(postition));
	triangle->setRotation(angle);
}

void DeserializeFromJson::act(Rectangle* rectangle)
{
	// Получаем координаты левой верхней точки в координатах фигуры
	QPointF lefTop = toQPointF(m_jsonObject->value("LeftTop").toString());
	// Получаем координаты второй точки в координатах фигуры
	QPointF destination
		= toQPointF(m_jsonObject->value("Destination").toString());
	// Получаем координаты фигуры в координатах сцены
	QPointF postition = toQPointF(m_jsonObject->value("Position").toString());
	// Получаем угол поворота фигуры
	qreal angle = m_jsonObject->value("Rotation").toDouble();
	// Высчитываем матрицу трансформации фигуры
	QTransform transform = toQTransform(postition, angle);

	// Отрисовывваем новый объект
	rectangle->act(StartDrawing{lefTop, postition});
	rectangle->act(CompleteDrawing{destination});
	// Задаем новому объекту матрицу трансформации
	rectangle->setPos(transform.map(postition));
	rectangle->setRotation(angle);
}

void DeserializeFromJson::act(SelectionRectangle* rectangle)
{
	Q_UNUSED(rectangle);
}

QPointF DeserializeFromJson::toQPointF(const QString& string)
{
	QRegularExpression regex{QString{"([+-]?\\d*\\.?\\d+)"}};

	// Итератор
	QRegularExpressionMatchIterator iter = regex.globalMatch(string);

	// Точка, куда пойдет запись
	QPointF temporary;
	if (iter.hasNext())
	{
		QRegularExpressionMatch matchX = iter.next();
		QRegularExpressionMatch matchY = iter.next();

		temporary.setX(matchX.captured(0).toDouble());
		temporary.setY(matchY.captured(0).toDouble());
	}

	return temporary;
}

QTransform DeserializeFromJson::toQTransform(const QPointF& position,
											 const qreal&	angle)
{
	QTransform transform;
	transform.translate(position.x(), position.y());
	transform.rotate(angle);
	transform.translate(-position.x(), -position.y());

	return transform;
}
