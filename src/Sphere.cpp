#pragma once
#include "stdafx.h"
#include "Sphere.h"

bool Sphere::hit(const Ray & ray, float t_min, float t_max, hit_record & rec ) const {
    vec3 sphereCenter = position;
    vec3 oc = ray.origin - sphereCenter;
    float a = vec3::dot(ray.direction, ray.direction);
    float b = 2.0f * vec3::dot(oc, ray.direction);
    float c = vec3::dot(oc, oc) - radius * radius;
    float discriminant = b*b - 4 * a*c;
    if (discriminant > 0) {
        float solution = (-b - sqrt(discriminant)) / (2.0f * a);
        if (solution > t_min && solution < t_max) {
            rec.t = solution;
            rec.p = ray.PointAtDistance(solution);
            rec.normal = (rec.p - sphereCenter) / radius; //normalize
            rec.pMat = pMat;
            return true;
        }

        solution = (-b + sqrt(discriminant)) / (2.0f * a);
        if (solution > t_min && solution < t_max) {
            rec.t = solution;
            rec.p = ray.PointAtDistance(solution);
            rec.normal = (rec.p - sphereCenter) / radius; //normalize
            rec.pMat = pMat;
            return true;
        }
    }
    return false;
}
