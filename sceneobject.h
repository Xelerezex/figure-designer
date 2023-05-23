#pragma once

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QGraphicsItem>

class Figures;

class SceneObject : public QGraphicsItem
{
protected:
	SceneObject(unsigned int id, Figures* figure, QGraphicsItem* graphics);


private:
	const unsigned int m_id;

	std::unique_ptr<Figures> m_figure;

	QGraphicsItem* m_graphics;
};
#endif // SCENEOBJECT_H
