#pragma once

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QGraphicsItem>

class Figures;

class SceneObject : public QGraphicsItem
{
protected:
    /*!
     * \brief Основной конструктор объекта
     * \param id - айди объекта
     */
    SceneObject(unsigned int id);

    /*!
     *  \brief Дефолтный деструктор
     */
    virtual ~SceneObject() = default;

    /*!
     * \brief Удаленные операторы
     */
    SceneObject()						  = delete;
    SceneObject(const SceneObject&)		  = delete;
    SceneObject(SceneObject&&)			  = delete;
    SceneObject& operator=(SceneObject&)  = delete;
    SceneObject& operator=(SceneObject&&) = delete;

private:
    /*!
     * \brief Айди объекта
     */
    const unsigned int m_id;
};

#endif // SCENEOBJECT_H
