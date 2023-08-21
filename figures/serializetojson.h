#ifndef SERIALIZETOJSON_H
#define SERIALIZETOJSON_H

#include "figureaction.h"

#include <QJsonObject>

class SerializeToJson : public FigureAction
{
	Q_DISABLE_COPY_MOVE(SerializeToJson);

public:
	/*!
	 * \brief Удаленный дефолтный конструткор
	 */
	SerializeToJson() = delete;

	/*!
	 * \brief Дефолтный констуктор
	 * \param jsonObject - указатель на объект, куда ведется запись
	 *        данных из фигуры
	 */
	explicit SerializeToJson(QJsonObject* jsonObject);

	/*!
	 * \brief Дефолтный деструктор
	 */
	~SerializeToJson() override = default;

	/*!
	 * \brief Дейстиве сериализации фигуры Круга
	 * \param circle - указатель на круг
	 */
	void act(Circle* circle) override;

	/*!
	 * \brief Дейстиве сериализации фигуры Квадрата
	 * \param circle - указатель на Квадрат
	 */
	void act(Square* square) override;

	/*!
	 * \brief Дейстиве сериализации фигуры Треугольника
	 * \param circle - указатель на Треугольник
	 */
	void act(Triangle* triangle) override;

	/*!
	 * \brief Дейстиве сериализации фигуры Прямоугольника
	 * \param circle - указатель на Прямоугольник
	 */
	void act(Rectangle* rectangle) override;

	/*!
	 * \brief Данный метод не должен использоваться
	 */
	void act(SelectionRectangle* rectangle) override;

private:
	/*!
	 * \brief Указатель на объект JSON
	 */
	QJsonObject* m_jsonObject;
};

#endif // SERIALIZETOJSON_H
