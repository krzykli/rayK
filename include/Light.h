#pragma once
#include "glm\glm.hpp"
#include "Object3d.h"

using namespace glm;

class Light: public Object3d
{
public:
    Light();
    ~Light();

    const vec3 GetPosition() const;
    void SetPosition(vec3 & p);

    const vec3 GetColor() const;
    void SetColor(vec3 & c);

    const float GetIntensity() const;
    void SetIntensity(float i);

    const float GetAttenuation() const;
    void SetAttenuation(float a);

    vec3 m_position;
    vec3 m_color;
    float m_intensity;
    float m_attenuation;

};

