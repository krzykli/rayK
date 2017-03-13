#ifndef RAYTRACERH
#define RAYTRACERH

#include "Ray.h"
#include "Camera.h"
#include "IHitable.h"
#include <vector>
#include "Scene.h"
#include "Light.h"

class Raytracer {
public:
    Raytracer() {}
    ~Raytracer() {}

    void Render(Camera &cam, std::vector<Light> & lightList, Scene &scene,
                const std::string &filename);

    void SetResolution(float res[2]);

    const float GetResolutionX() const;

    const float GetResolutionY() const;

    void SetAASamples(int samples);

private:
    vec3 Trace(Ray &r, std::vector<Light> & lightList, Scene &scene, int depth);
    float m_renderResolution[2] = { 512.0, 512.0 };
    int m_aaSamples = 0;
    int m_rayDepth = 5;
};

#endif // RAYTRACERH
