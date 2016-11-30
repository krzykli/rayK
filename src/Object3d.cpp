#include "stdafx.h"
#include "Object3d.h"
#include <math.h>
#include "Logger.hpp"

Object3d::Object3d() :
    m_name("Object"),
    m_pParent(NULL),
    m_children(NULL),
    m_transform(Transformation()),
    m_pMat(NULL)
{
    
}

Object3d::~Object3d()
{
}

void Object3d::SetTransform(Transformation & in_transform) 
{
    m_transform = in_transform;
}

const Transformation & Object3d::GetTransform() const 
{
    return m_transform;
}

void Object3d::SetParent(Object3d * in_pParent)
{
    m_pParent = in_pParent;
    in_pParent->m_children.push_back(this);
}

Object3d const * Object3d::GetParent() const
{
    return m_pParent;
}

void Object3d::SetName(const std::string & in_name)
{
    m_name = in_name;
}

const std::string & Object3d::GetName() const
{
    return m_name;
}

std::list<Object3d *> Object3d::GetChildren() const
{
    return m_children;
}
