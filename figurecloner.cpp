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
	auto* square = qgraphicsitem_cast<Square*>(item);

	// Координаты фигуры
	const auto figureCoord{square->pos().toPoint() + square->center()};

	// Создаем новый объект и настраиваем
	auto* newSquare = new Square{};
	newSquare->act(StartDrawing{square->center(), figureCoord});
	newSquare->act(CompleteDrawing{square->destination()});
	newSquare->setSelected(true);
	// Разместить фигуру выше на слой
	newSquare->setZValue(newSquare->zValue() + 0.1);

	return newSquare;
}

Rectangle* FigureCloner::cloneRectangle(QGraphicsItem* item)
{
	auto* rectangle = qgraphicsitem_cast<Rectangle*>(item);

	// Координаты фигуры
	const auto figureCoord{rectangle->pos().toPoint() + rectangle->leftTop()};

	// Создаем новый объект и настраиваем
	auto* newRectangle = new Rectangle{};
	newRectangle->act(StartDrawing{rectangle->leftTop(), figureCoord});
	newRectangle->act(CompleteDrawing{rectangle->destination()});
	newRectangle->setSelected(true);
	// Разместить фигуру выше на слой
	newRectangle->setZValue(newRectangle->zValue() + 0.1);

	return newRectangle;
}

Triangle* FigureCloner::cloneTriangle(QGraphicsItem* item)
{
	auto* triangle = qgraphicsitem_cast<Triangle*>(item);

	// Координаты фигуры
	const auto firstDotCoord{triangle->pos().toPoint() + triangle->first()};

	// Создаем новый объект и настраиваем
	auto* newTriangle = new Triangle{};
	newTriangle->act(StartDrawing{triangle->first(), firstDotCoord});
	newTriangle->act(CompleteDrawing{triangle->second()});
	newTriangle->act(CompleteDrawing{triangle->third()});
	newTriangle->setSelected(true);
	// Разместить фигуру выше на слой
	newTriangle->setZValue(newTriangle->zValue() + 0.1);

	return newTriangle;
}

Circle* FigureCloner::cloneCircle(QGraphicsItem* item)
{
	auto* circle = qgraphicsitem_cast<Circle*>(item);

	// Координаты фигуры
	const auto figureCoord{circle->pos().toPoint() + circle->center()};

	// Создаем новый объект и настраиваем
	auto* newCircle = new Circle{};
	newCircle->act(StartDrawing{circle->center(), figureCoord});
	newCircle->act(CompleteDrawing{circle->destination()});
	newCircle->setSelected(true);
	// Разместить фигуру выше на слой
	newCircle->setZValue(newCircle->zValue() + 0.1);

	return newCircle;
}
