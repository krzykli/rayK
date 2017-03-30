#ifndef RAYH
#define RAYH

#include "vec3.h"

class Ray
{
public:

    Ray() {}

    Ray(const vec3& origin, const vec3 & direction);

    vec3 GetOrigin() const;

    vec3 GetDirection() const;

    vec3 PointAtDistance(float t) const;

private:
    vec3 origin;
    vec3 direction;
};

#endif // RAYH
