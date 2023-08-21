#ifndef DESERIALIZEFROMJSON_H
#define DESERIALIZEFROMJSON_H

#include "figureaction.h"

#include <QJsonObject>
#include <QPointF>

class DeserializeFromJson : public FigureAction
{
	Q_DISABLE_COPY_MOVE(DeserializeFromJson);

public:
	/*!
	 * \brief Удаленный дефолтный конструткор
	 */
	DeserializeFromJson() = delete;

	/*!
	 * \brief Дефолтный констуктор
	 * \param jsonObject - указатель на объект, куда ведется запись
	 *        данных из фигуры
	 */
	explicit DeserializeFromJson(QJsonObject* jsonObject);

	/*!
	 * \brief Дефолтный деструктор
	 */
	~DeserializeFromJson() override = default;

	/*!
	 * \brief Дейстиве десериализации фигуры Круга
	 * \param circle - указатель на Круг
	 */
	void act(Circle* circle) override;

	/*!
	 * \brief Дейстиве десериализации фигуры Квадрата
	 * \param circle - указатель на Квадрат
	 */
	void act(Square* square) override;

	/*!
	 * \brief Дейстиве десериализации фигуры Треугольника
	 * \param circle - указатель на Треугольник
	 */
	void act(Triangle* triangle) override;

	/*!
	 * \brief Дейстиве десериализации фигуры Прямоугольника
	 * \param circle - указатель на Прямоугольник
	 */
	void act(Rectangle* rectangle) override;

	/*!
	 * \brief Данный метод не должен использоваться
	 */
	void act(SelectionRectangle* rectangle) override;

private:
	/*!
	 * \brief Функция парсит строку и возвращает точку
	 * \param string - строка на вход
	 * \return координата
	 */
	[[nodiscard]] static QPointF toQPointF(const QString& string);

	/*!
	 * \brief Функция парсит угол и возвращает матрицу трансформации
	 *        (Для парвильной отработки фигура уже должна быть на сцене)
	 * \param angle - строка на вход
	 * \return матрица трансформации
	 */
	[[nodiscard]] QTransform toQTransform(const QPointF& position,
										  const qreal&	 angle);

private:
	/*!
	 * \brief Указатель на объект JSON
	 */
	QJsonObject* m_jsonObject;
};

#endif // DESERIALIZEFROMJSON_H
