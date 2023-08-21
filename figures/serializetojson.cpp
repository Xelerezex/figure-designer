#include "serializetojson.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

SerializeToJson::SerializeToJson(QJsonObject* jsonObject)
	: m_jsonObject{jsonObject}
{
}

void SerializeToJson::act(Circle* circle)
{
}

void SerializeToJson::act(Square* square)
{
	// Запомнить Тип
	m_jsonObject->insert("Type", QJsonValue::fromVariant(square->type()));

	// Запомнить Координаты Центра
	m_jsonObject->insert(
		"Center",
		QJsonValue::fromVariant((QString{"(%1,%2)"}
									 .arg(square->center().x())
									 .arg(square->center().y()))));

	// Запомнить Координаты Второй точки
	m_jsonObject->insert(
		"Destination",
		QJsonValue::fromVariant((QString{"(%1,%2)"}
									 .arg(square->destination().x())
									 .arg(square->destination().y()))));

	// Запомнить Координаты Позиции на сцене
	m_jsonObject->insert(
		"Position",
		QJsonValue::fromVariant((
			QString{"(%1,%2)"}.arg(square->pos().x()).arg(square->pos().y()))));

	// Запомнить Угол поворота Фигуры
	m_jsonObject->insert("Rotation",
						 QJsonValue::fromVariant(square->rotation()));
}

void SerializeToJson::act(Triangle* triangle)
{
}

void SerializeToJson::act(Rectangle* rectangle)
{
	// Запомнить Тип
	m_jsonObject->insert("Type", QJsonValue::fromVariant(rectangle->type()));

	// Запомнить Координаты Центра
	m_jsonObject->insert(
		"LeftTop",
		QJsonValue::fromVariant((QString{"(%1,%2)"}
									 .arg(rectangle->leftTop().x())
									 .arg(rectangle->leftTop().y()))));

	// Запомнить Координаты Второй точки
	m_jsonObject->insert(
		"Destination",
		QJsonValue::fromVariant((QString{"(%1,%2)"}
									 .arg(rectangle->destination().x())
									 .arg(rectangle->destination().y()))));

	// Запомнить Координаты Позиции на сцене
	m_jsonObject->insert(
		"Position",
		QJsonValue::fromVariant((QString{"(%1,%2)"}
									 .arg(rectangle->pos().x())
									 .arg(rectangle->pos().y()))));

	// Запомнить Угол поворота Фигуры
	m_jsonObject->insert("Rotation",
						 QJsonValue::fromVariant(rectangle->rotation()));
}

void SerializeToJson::act(SelectionRectangle* rectangle)
{
	Q_UNUSED(rectangle);
}
