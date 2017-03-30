#ifndef LIGHTH
#define LIGHTH

#include "vec3.h"
#include "Object3d.h"

struct Light: public Object3d
{
    Light();
    ~Light();

    vec3 position;
    vec3 color;
    float intensity;
    float attenuation;

};

#endif // LIGHTH
