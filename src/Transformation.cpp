#include "stdafx.h"
#include "Transformation.h"

#define M_PI 3.14159265358979323846  /* pi */

// TODO: Move both functions to math util module
inline double DegreesToRadians(const double in_degrees)
{ return in_degrees * M_PI / 180.0; }

inline double RadiansToDegrees(const double in_radians)
{ return in_radians * 180.0 / M_PI; }


// Initalize transform to identity
Transformation::Transformation()
{
    m_rotation = mat4(0);
    m_rotation[3][3] = 1;

    m_translation = mat4(1);

    m_scale = mat4(1);

    m_xform = mat4(0);
    m_xform[3][3] = 1;
}

Transformation::~Transformation()
{
}


mat4 Transformation::GetMatrix4() const 
{
    return m_translation * m_rotation * m_scale;
}

void Transformation::SetMatrix4(const mat4 & in_matrix) 
{
    m_xform = in_matrix;
}

void Transformation::SetTranslate(const vec3 &t)
{
    vec4 translate(t, 1);
    m_translation[3] = vec4(translate);
}

vec3 Transformation::GetTranslation() const
{
    return vec3(this->m_translation[3]);
}

void Transformation::SetRotateAroundAxis(const float degrees, const vec3 & in_v3Axis)
{
    float theta = DegreesToRadians(degrees);
    mat3 A = mat3(0, in_v3Axis.z, -1 * in_v3Axis.y,
                 -1 * in_v3Axis.z, 0, in_v3Axis.x,
                  in_v3Axis.y, -1 * in_v3Axis.x, 0);
    mat3 rot = mat3(1.0) + A * sin(theta) + A*A*(1 - cos(theta));
    mat4 R = mat4(rot);
    R[3] = vec4(0, 0, 0, 1);
    m_rotation = R;
}

void Transformation::SetRotateX(const float degrees)
{
    Transformation::SetRotateAroundAxis(degrees, vec3(1, 0, 0));
}

void Transformation::SetRotateY(const float degrees)
{
    Transformation::SetRotateAroundAxis(degrees, vec3(0, 1, 0));
}

void Transformation::SetRotateZ(const float degrees)
{
    Transformation::SetRotateAroundAxis(degrees, vec3(0, 0, 1));
}

void Transformation::SetRotateXYZ(const vec3 & rot)
{
    Transformation::SetRotateX(rot.x);
    Transformation::SetRotateY(rot.y);
    Transformation::SetRotateZ(rot.z);
}

void Transformation::SetScale(const vec3 & in_v3Scale)
{
    mat4 S = mat4(1);
    for (int i = 0; i < 3; i++) {
        S[i][i] = in_v3Scale[i];
    }
    m_scale = S;
}

