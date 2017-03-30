#pragma once
#include "stdafx.h"
#include "Ray.h"

Ray::Ray(const vec3& origin, const vec3& direction) :
    origin(origin),
    direction(direction)
{}

vec3 Ray::GetOrigin() const {
    return origin;
}

vec3 Ray::GetDirection() const {
    return direction;
}

vec3 Ray::PointAtDistance(float t) const {
    return origin + t * direction;
}
