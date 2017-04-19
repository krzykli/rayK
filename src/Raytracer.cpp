#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <algorithm>

#include "rayK_defines.h"
#include "Camera.h"
#include "Sphere.h"
#include "Scene.h"

struct Raytracer {
    int renderResolution[2];
    int aaSamples = 0;
    int rayDepth = 5;

    vec3 Trace(const Ray& r,
               std::vector<Light*>& lightList,
               Scene& scene,
               int depth)
    {
        vec3 color = vec3(0, 0, 0);
        hit_record rec;

        if (depth >= rayDepth) {
            return color;
        }
        if (scene.hit(r, 0.00001f, FLT_MAX, rec)) {
            if (rec.pMat == NULL) {
                return vec3(0, 0, 0);
            }

            for (std::vector<Light*>::iterator it = lightList.begin(); it != lightList.end(); ++it) {
                Light lgt = **it;
                vec3 lightPos = lgt.position;
                float distToLight = (lightPos - rec.p).length();
                vec3 diffuseColor = rec.pMat->diffuse;

                vec3 dirToCamera = -vec3::normalize(r.direction);
                vec3 dirToLight = vec3::normalize(lightPos - rec.p);
                vec3 halfVector = vec3::normalize(dirToCamera + dirToLight);

                float specularity = 0.6f;
                float shininess = 80;

                Ray shadowRay = Ray(rec.p, dirToLight + vec3(0.2f) * vec3(randf, randf, randf));
                if (scene.hit(shadowRay, 0.00001f, FLT_MAX, rec)) {
                    color += vec3(0, 0, 0);
                }
                else {
                    vec3 shadingModel = (lgt.intensity / pow(distToLight, lgt.attenuation) *
                        diffuseColor * (std::max)(vec3::dot(rec.normal, vec3::normalize(lightPos - rec.p)), 0.f) * lgt.color +
                        specularity * pow((std::max)(vec3::dot(rec.normal, halfVector), 0.f), shininess));
                    color += shadingModel;
                }

                Ray bounce;
                if (rec.pMat->scatter(r, rec, bounce)) {
                    color += vec3(0.2f) * Trace(bounce, lightList, scene, depth++);
                }
            }

            return (vec3::minimum)(color, vec3(1));
        }
        float v = 0.5f * (vec3::normalize(r.direction).y() + 1);
        return vec3(v, v, v);
    }


    void Render(Camera &cam,
                std::vector<Light*> &lightList,
                Scene &scene,
                win32_offscreen_buffer *Buffer,
                void (*UpdateWindowCallback)(void))
    {
        clock_t begin = clock();

        uint32 *Pixel = (uint32 *)Buffer->Memory;
        for(int i = Buffer->Height; i > 0; --i)
        {
            for(int j = 0; j < Buffer->Width; ++j)
            {
                vec3 color = vec3(0, 0, 0);

                if (aaSamples > 1) {
                    for (int s = 0; s < aaSamples; s++)
                    {
                        // pixel centers + jitter
                        float u = float(j + randf) / float(Buffer->Width);
                        float v = float(i + randf) / float(Buffer->Height);

                        Ray r = cam.GetRay(u, v);
                        color += Trace(r, lightList, scene, 0);
                    }
                    color /= float(aaSamples);
                }
                else {
                    float u = float(j) / float(Buffer->Width);
                    float v = float(i) / float(Buffer->Height);

                    Ray r = cam.GetRay(u, v);
                    color = Trace(r, lightList, scene, 0);
                }

                uint8 red = (uint8)(color[0] * 255.99);
                uint8 green = (uint8)(color[1] * 255.99);
                uint8 blue = (uint8)(color[2] * 255.99);

                *Pixel++ = ((red << 16) | (green << 8) | blue);
            }

            UpdateWindowCallback();
        }

        clock_t end = clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        printf("%f", elapsed_secs);
    }
};
