#pragma once
#include "stdafx.h"
#include "Object3d.h"
#include "IHitable.h"
#include <vector>

class Scene : public IHitable
{
public:
    Scene() {};

    virtual bool hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const;

    size_t GetChildrenNumber() const;

    void AddObject(Object3d * obj);

private:
    unsigned int m_objNumber;
    std::vector<Object3d *> m_flatObjList;
};

