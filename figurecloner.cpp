#include "figurecloner.h"

#include "square.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

#include "startdrawing.h"
#include "completedrawing.h"

#include <QGraphicsSceneMouseEvent>

Square* FigureCloner::cloneSquare(QGraphicsItem* item)
{
	// Указатель на копируемый объект
	auto* square = qgraphicsitem_cast<Square*>(item);
	// Матрица трансформации копируемого объекта
	QTransform transform{square->transform()};

	// Координаты фигуры
	const auto figureCoord{transform.map(square->pos()).toPoint()
						   + square->center()};

	// Создаем новый объект и настраиваем
	auto* newSquare = new Square{};
	newSquare->act(StartDrawing{square->center(), figureCoord});
	newSquare->act(CompleteDrawing{square->destination()});
	// Задаем новому объекту матрицу трансформаций старого
	newSquare->setPos(transform.map(item->pos()));
	newSquare->setRotation(square->rotation());

	return newSquare;
}

Rectangle* FigureCloner::cloneRectangle(QGraphicsItem* item)
{
	// Указатель на копируемый объект
	auto* rectangle = qgraphicsitem_cast<Rectangle*>(item);
	// Матрица трансформации копируемого объекта
	QTransform transform{rectangle->transform()};

	// Координаты фигуры
	const auto figureCoord{transform.map(rectangle->pos()).toPoint()
						   + rectangle->leftTop()};

	// Создаем новый объект и настраиваем
	auto* newRectangle = new Rectangle{};
	newRectangle->act(StartDrawing{rectangle->leftTop(), figureCoord});
	newRectangle->act(CompleteDrawing{rectangle->destination()});
	// Задаем новому объекту матрицу трансформаций старого
	newRectangle->setPos(transform.map(item->pos()));
	newRectangle->setRotation(rectangle->rotation());

	return newRectangle;
}

Triangle* FigureCloner::cloneTriangle(QGraphicsItem* item)
{
	// Указатель на копируемый объект
	auto* triangle = qgraphicsitem_cast<Triangle*>(item);
	// Матрица трансформации копируемого объекта
	QTransform transform{triangle->transform()};
	// Координаты фигуры
	const auto firstDotCoord{transform.map(triangle->pos()).toPoint()
							 + triangle->first()};

	// Создаем новый объект и настраиваем
	auto* newTriangle = new Triangle{};
	newTriangle->act(StartDrawing{triangle->first(), firstDotCoord});
	newTriangle->act(CompleteDrawing{triangle->second()});
	newTriangle->act(CompleteDrawing{triangle->third()});
	// Задаем новому объекту матрицу трансформаций старого
	newTriangle->setPos(transform.map(item->pos()));
	newTriangle->setRotation(triangle->rotation());

	return newTriangle;
}

Circle* FigureCloner::cloneCircle(QGraphicsItem* item)
{
	// Указатель на копируемый объект
	auto* circle = qgraphicsitem_cast<Circle*>(item);
	// Матрица трансформации копируемого объекта
	QTransform transform{circle->transform()};
	// Координаты фигуры
	const auto figureCoord{transform.map(circle->pos()).toPoint()
						   + circle->center()};

	// Создаем новый объект и настраиваем
	auto* newCircle = new Circle{};
	newCircle->act(StartDrawing{circle->center(), figureCoord});
	newCircle->act(CompleteDrawing{circle->destination()});
	// Задаем новому объекту матрицу трансформаций старого
	newCircle->setPos(transform.map(item->pos()));
	newCircle->setRotation(circle->rotation());

	return newCircle;
}
