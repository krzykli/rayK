#include "stdafx.h"
#include "Camera.h"
#include "math.h"
#define M_PI 3.14159265358979323846  /* pi */


vec3 random_in_unit_disc() {
    vec3 p;
    do {
        p = vec3(2.0) * vec3(randf, randf, 0) - vec3(1, 1, 0);
    } while (dot(p, p) >= 1.0);
    return p;
}


Camera::Camera(vec3 & pos, vec3 & lookAt, vec3 & upV, float fov, float aspectRatio, float focus_dist) :
    m_Pos(pos),
    m_LookAt(lookAt),
    m_UpVector(upV),
    m_Fov(fov)
{
    // Create coordinate frame
    w = normalize(m_Pos - m_LookAt);
    u = normalize(cross(m_UpVector, w));
    v = cross(w, u);

    float theta = fov * M_PI / 180; // convert to radians
    float half_height = tan(theta / 2);
    float half_width = aspectRatio * half_height;

    m_HorizontalVector = 2 * half_width * u * focus_dist;
    m_VerticalVector = 2 * half_height * v * focus_dist;
    m_TopLeftCorner = m_Pos - w - half_width * u * focus_dist - half_height * v * focus_dist - focus_dist * w;
}

Ray Camera::GetRay(float s, float t) const 
{
    // aperature 
    vec3 rd = vec3(0.5) * random_in_unit_disc();
    vec3 offset = u * rd.x + v * rd.y;
    return Ray(m_Pos + offset, m_TopLeftCorner + s * m_HorizontalVector + t * m_VerticalVector - m_Pos - offset);
}


Camera::~Camera()
{
}
