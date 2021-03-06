#pragma once
#include "stdafx.h"
#include "IHitable.h"
#include <vector>

struct Scene : public IHitable
{
    unsigned int objNumber = 0;
    unsigned int lightNumber = 0;

    void* flatObjList[100]; // hardcore this for now
    Light* lightList[100]; // hardcode this for now

    virtual bool hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const;

    size_t GetLightsNumber() const;

    size_t GetChildrenNumber() const;

    void AddObject(void* obj, int index);

    void AddLight(Light* obj, int index);
};

