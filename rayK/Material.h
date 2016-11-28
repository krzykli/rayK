#pragma once
#include "glm\glm.hpp"

using namespace glm;

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