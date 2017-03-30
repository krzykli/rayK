#include "stdafx.h"
#include "Light.h"


Light::Light() :
    position(vec3(0, 0, 0)),
    color(vec3(1, 1, 1)),
    attenuation(2.0f),
    intensity(6.0f)
{
}


Light::~Light()
{
}

