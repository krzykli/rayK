#pragma once
#include "IHitable.h"
#include "Object3d.h"

class Triangle : public Object3d, public IHitable {
public:
    Triangle(vec3 & a, vec3 & b, vec3 & c);
    Triangle(vec3 verts[3]);
    virtual bool hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const;

    vec3 m_verts[3], m_A, m_B, m_C, m_normal;
};
