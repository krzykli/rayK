#ifndef TRIANGLEH
#define TRIANGLEH

#include "IHitable.h"
#include "Object3d.h"

struct Triangle : public Object3d, public IHitable {
    Triangle(const vec3 & a, const vec3 & b, const vec3 & c);
    Triangle(vec3 verts[3]);
    virtual bool hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const;

    vec3 verts[3], A, B, C, _normal;
};
#endif // TRIANGLEH
