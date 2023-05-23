#include "sceneobject.h"

#include "figures.h"

SceneObject::SceneObject(unsigned int id, Figures* figure, QGraphicsItem* graphics)
	: m_id{id}
	, m_figure{figure}
	, m_graphics{graphics}
{
}
