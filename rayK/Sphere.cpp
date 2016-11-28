#pragma once
#include "stdafx.h"
#include "Sphere.h"

bool Sphere::hit(const Ray & ray, float t_min, float t_max, hit_record & rec ) const {
    vec3 sphereCenter = GetTransform().GetTranslation();
    vec3 oc = ray.GetOrigin() - sphereCenter;
    float a = dot(ray.GetDirection(), ray.GetDirection());
    float b = 2.0 * dot(oc, ray.GetDirection());
    float c = dot(oc, oc) - m_radius * m_radius;
    float discriminant = b*b - 4 * a*c;
    if (discriminant > 0) {
        float solution = (-b - sqrt(discriminant)) / (2.0 * a);
        if (solution > t_min && solution < t_max) {
            rec.t = solution;
            rec.p = ray.PointAtDistance(solution);
            rec.normal = (rec.p - sphereCenter) / m_radius; //normalize
            rec.pMat = GetMaterial();
            return true;
        }

        solution = (-b + sqrt(discriminant)) / (2.0 * a);
        if (solution > t_min && solution < t_max) {
            rec.t = solution;
            rec.p = ray.PointAtDistance(solution);
            rec.normal = (rec.p - sphereCenter) / m_radius; //normalize
            rec.pMat = GetMaterial();
            return true;
        }
    }
    return false;
}