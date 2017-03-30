#ifndef RAYH
#define RAYH

#include "vec3.h"

struct Ray
{
    vec3 origin;
    vec3 direction;

    Ray() {}

    Ray(const vec3& origin, const vec3 & direction);

    vec3 PointAtDistance(float t) const;

};

#endif // RAYH
