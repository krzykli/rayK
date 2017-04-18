#ifndef RAYH
#define RAYH

#include "vec3.h"

struct Ray
{
    vec3 origin;
    vec3 direction;

    Ray() {}

    Ray(const vec3& origin, const vec3& direction):
        origin(origin),
        direction(direction)
    {}

    vec3 PointAtDistance(float t) const {
        return origin + t * direction;
    }

};

#endif // RAYH
