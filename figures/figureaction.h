#ifndef FIGUREACTION_H
#define FIGUREACTION_H

class Circle;
class Square;
class Triangle;
class Rectangle;

class FigureAction
{
public:
	virtual void act(class Circle*)	   = 0;
	virtual void act(class Square*)	   = 0;
	virtual void act(class Triangle*)  = 0;
	virtual void act(class Rectangle*) = 0;
};

#endif // FIGUREACTION_H
