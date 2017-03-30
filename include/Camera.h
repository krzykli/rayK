#ifndef CAMERAH
#define CAMERAH

#include "vec3.h"
#include "Object3d.h"
#include "Ray.h"

struct Camera : public Object3d
{
    vec3 u, v, w; // coordinate frame
    vec3 position;
    vec3 lookAt;
    vec3 upVector;
    float aperature;
    float resX;
    float resY;
    vec3 topLeftCorner;
    vec3 horizontalVector;
    vec3 verticalVector;
    float fov;

    Camera(const vec3 &pos, const vec3 &lookAt, const vec3 &upV,
           float fovy, float aspectRatio, float focus_dist);

    Ray GetRay(float u, float v) const;

    ~Camera();

};

#endif // CAMERAH
