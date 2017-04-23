#ifndef SPHEREH
#define SPHEREH

#include "IHitable.h"
#include "Lambert.h"
#include "vec3.h"

struct Sphere: public IHitable {
    float radius;
    vec3 position;
    Material* pMat;

    Sphere() {}
    Sphere(float r) : radius(r) {}
    virtual bool hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const;

};

#endif // SPHEREH
