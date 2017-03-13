#ifndef MATERIALH
#define MATERIALH

#include "vec3.h"


struct hit_record;
class Ray;

class Material
{
public:
    virtual bool scatter(const Ray& ray, const hit_record& rec, Ray & bounce) const = 0;

    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    vec3 emission;
};

#endif // MATERIALH
