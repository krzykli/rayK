#ifndef LIGHTH
#define LIGHTH

#include "vec3.h"

struct Light
{
    vec3 position;
    vec3 color;
    float intensity;
    float attenuation;

    Light() :
        position(vec3(0, 0, 0)),
        color(vec3(1, 1, 1)),
        attenuation(2.0f),
        intensity(6.0f)
    {
    }

    Light::~Light()
    {
    }
};

#endif // LIGHTH
