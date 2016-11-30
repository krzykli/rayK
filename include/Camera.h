#pragma once
#include "glm\glm.hpp"
#include "Object3d.h"
#include "Ray.h"

using namespace glm;

class Camera : public Object3d
{
public:
    Camera(vec3 &pos, vec3 &lookAt, vec3 &upV, float fovy, float aspectRatio, float focus_dist);

    Ray GetRay(float u, float v) const;

    ~Camera();

private:
    vec3 m_Pos;
    vec3 m_LookAt;
    vec3 m_UpVector;
    float m_resX;
    float m_resY;
    vec3 m_TopLeftCorner;
    vec3 m_HorizontalVector;
    vec3 m_VerticalVector;
    float m_Fov;
    vec3 u, v, w;
};
