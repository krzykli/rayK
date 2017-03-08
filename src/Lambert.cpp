#include "stdafx.h"
#include "Lambert.h"
#include "Ray.h"
#include "IHitable.h"
#include "vec3.h"


vec3 random_in_unit_sphere() {
    vec3 p;
    p = vec3(2.0) * vec3(randf, randf, randf) - vec3(1, 1, 1); //vector <-1.1>
    return p;
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * vec3::dot(v, n) * n;
}

Lambert::Lambert() {
    diffuse = vec3(0.7, 0.7, 0.7);
}

bool Lambert::scatter(const Ray& ray, const hit_record& rec, Ray & bounce) const 
{
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    vec3 reflected = reflect(vec3::normalize(ray.GetDirection()), rec.normal);
    //bounce = Ray(rec.p, reflected);
    bounce = Ray(rec.p, reflected + vec3(0.5) * random_in_unit_sphere());
    return (vec3::dot(bounce.GetDirection(), rec.normal) > 0);
}
