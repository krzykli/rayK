#ifndef IHITABLEH
#define IHITABLEH

#pragma once

#include "Ray.h"

class Material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    Material * pMat;
};

struct IHitable
{
    virtual bool hit(const Ray &ray, float t_min, float t_max,hit_record & rec) const = 0;
};

#endif // IHITABLEH
