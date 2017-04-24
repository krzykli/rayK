#include "stdafx.h"
#include "Camera.h"
#include "math.h"
#define M_PI 3.14159265358979323846f  /* pi */


vec3 random_in_unit_disc() {
    vec3 p;
    do {
        p = vec3(2.0) * vec3(randf, randf, 0) - vec3(1, 1, 0);
    } while (vec3::dot(p, p) >= 1.0);
    return p;
}


Camera::Camera(const vec3 & pos, const vec3 & lookAt, const vec3 & upV,
               float fov, float aspectRatio, float focus_dist) :
    position(pos),
    lookAt(lookAt),
    upVector(upV),
    fov(fov),
    aperature(0.f)
{
    // Create coordinate frame
    w = vec3::normalize(position - lookAt);
    u = vec3::normalize(vec3::cross(upVector, w));
    v = vec3::cross(w, u);

    float theta = fov * M_PI / 180.0f; // convert to radians
    float half_height = tan(theta / 2);
    float half_width = aspectRatio * half_height;

    horizontalVector = 2 * half_width * u * focus_dist;
    verticalVector = 2 * half_height * v * focus_dist;
    topLeftCorner = (position - w - half_width * u * focus_dist -
                     half_height * v * focus_dist - focus_dist * w);
}

Ray Camera::GetRay(float s, float t) const
{
    // aperature
    vec3 rd = vec3(0);
    if (this->aperature > 0) {
        rd = vec3(this->aperature) * random_in_unit_disc();
    }
    vec3 offset = u * rd.x() + v * rd.y();
    return Ray(position + offset, topLeftCorner + s * horizontalVector +
               t * verticalVector - position - offset);
}


Camera::~Camera()
{
}
