#pragma once

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QGraphicsItem>

class Figures;

class SceneObject : public QGraphicsItem
{
protected:
    SceneObject(unsigned int id);

private:
    const unsigned int m_id;
};

#endif // SCENEOBJECT_H
