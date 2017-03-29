#ifndef TRIANGLEH
#define TRIANGLEH

#include "IHitable.h"
#include "Object3d.h"

class Triangle : public Object3d, public IHitable {
public:
    Triangle(const vec3 & a, const vec3 & b, const vec3 & c);
    Triangle(vec3 verts[3]);
    virtual bool hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const;

    vec3 m_verts[3], m_A, m_B, m_C, m_normal;
};
#endif // TRIANGLEH
