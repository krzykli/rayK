#pragma once
#include "glm\glm.hpp"
using namespace glm;

class Ray
{
public:

    Ray() {}

    Ray(const vec3& origin, const vec3 & direction);

    vec3 GetOrigin() const;

    vec3 GetDirection() const;

    vec3 PointAtDistance(float t) const;

private:
    vec3 m_origin;
    vec3 m_direction;
};
