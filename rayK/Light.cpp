#include "stdafx.h"
#include "Light.h"


Light::Light() :
    m_position(vec3(0, 0, 0)),
    m_color(vec3(1, 1, 1)),
    m_attenuation(2.0),
    m_intensity(5.0)
{
}


Light::~Light()
{
}

const vec3 Light::GetPosition() const
{
    return m_position;
}

void Light::SetPosition(vec3 & p)
{
    m_position = p;
}

const vec3 Light::GetColor() const
{
    return m_color;
}

void Light::SetColor(vec3 & c)
{
    m_color = c;
}

const float Light::GetIntensity() const
{
    return m_intensity;
}

void Light::SetIntensity(float i)
{
    m_intensity = i;
}

const float Light::GetAttenuation() const
{
    return m_attenuation;
}

void Light::SetAttenuation(float a)
{
    m_attenuation = a;
}
