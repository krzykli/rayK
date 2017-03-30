#ifndef SPHEREH
#define SPHEREH

#include "IHitable.h"
#include "Object3d.h"
#include "Lambert.h"
#include "vec3.h"

class Sphere : public Object3d, public IHitable {
public:
    Sphere() {}
    Sphere(float r) : radius(r) {}
    virtual bool hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const;

    float radius;
    vec3 position;
};

#endif // SPHEREH
