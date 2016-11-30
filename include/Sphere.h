#pragma once
#include "IHitable.h"
#include "Object3d.h"
#include "Lambert.h"

class Sphere : public Object3d, public IHitable {
public:
    Sphere() {}
    Sphere(float r) : m_radius(r) {}
    virtual bool hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const;

    float m_radius;
};
