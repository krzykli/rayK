#ifndef RAYTRACERH
#define RAYTRACERH

#include "Ray.h"
#include "Camera.h"
#include "IHitable.h"
#include <vector>
#include "Scene.h"
#include "Light.h"

struct Raytracer {

    int renderResolution[2] = {512, 512};
    int aaSamples = 0;
    int rayDepth = 5;

    Raytracer() {}
    ~Raytracer() {}

    void Render(Camera &cam, std::vector<Light> & lightList, Scene &scene,
                const std::string &filename);

    vec3 Trace(const Ray &r, std::vector<Light> & lightList, Scene &scene, int depth);
};

#endif // RAYTRACERH
