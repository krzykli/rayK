#include "stdafx.h"
#include "Object3d.h"
#include <math.h>

Object3d::Object3d() :
    name("Object"),
    pParent(NULL),
    children(NULL),
    pMat(NULL)
{
}

Object3d::~Object3d()
{
}


void Object3d::SetParent(Object3d * in_pParent)
{
    pParent = in_pParent;
    in_pParent->children.push_back(this);
}

Object3d const * Object3d::GetParent() const
{
    return pParent;
}

void Object3d::SetName(const std::string & in_name)
{
    name = in_name;
}

const std::string & Object3d::GetName() const
{
    return name;
}

std::list<Object3d *> Object3d::GetChildren() const
{
    return children;
}
