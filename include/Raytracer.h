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

    void SetResolution(int res[2]);

    const int GetResolutionX() const;

    const int GetResolutionY() const;

    void SetAASamples(int samples);

private:
    vec3 Trace(const Ray &r, std::vector<Light> & lightList, Scene &scene, int depth);
    int renderResolution[2] = { 512, 512 };
    int aaSamples = 0;
    int rayDepth = 5;
};

#endif // RAYTRACERH
