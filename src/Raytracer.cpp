#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Raytracer.h"
#include "Camera.h"
#include "Logger.hpp"
#include "Sphere.h"
#include "Scene.h"

vec3 Raytracer::Trace(
    const Ray& r, std::vector<Light>& lightList, Scene& scene, int depth)
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

        for (std::vector<Light>::iterator it = lightList.begin(); it != lightList.end(); ++it) {
            Light lgt = *it;
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
                    diffuseColor * std::max(vec3::dot(rec.normal, vec3::normalize(lightPos - rec.p)), 0.f) * lgt.color +
                    specularity * pow(std::max(vec3::dot(rec.normal, halfVector), 0.f), shininess));
                color += shadingModel;
            }

            Ray bounce;
            if (rec.pMat->scatter(r, rec, bounce)) {
                color += vec3(0.2f) * Trace(bounce, lightList, scene, depth++);
            }
        }

        return vec3::min(color, vec3(1));
    }
    float v = 0.5f * (vec3::normalize(r.direction).y() + 1);
    return vec3(v, v, v);
}


void writeBucketToFile(std::ofstream & fileHandler, vec3 arr[], int arrSize) {
    for (int i = 0; i < arrSize; i++)
    {
        fileHandler << arr[i].x() << " " << arr[i].y() << " " << arr[i].z() << "\n";
    }
}

void Raytracer::Render(Camera & cam, std::vector<Light> & lightList, Scene & scene, const std::string & filename)
{
    clock_t begin = clock();

    std::ofstream outputFile;
    outputFile.open(filename);

    const int bucketSize = 5024;
    vec3 bufferedPixels[bucketSize];
    int pixelNumber = 0;

    int width = renderResolution[0];
    int height = renderResolution[1];

    outputFile << "P3\n" << width << " " << height << "\n255\n";

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {

            vec3 color = vec3(0, 0, 0);

            if (aaSamples > 1) {
                for (int s = 0; s < aaSamples; s++)
                {
                    // pixel centers + jitter
                    float u = float(i + randf) / float(width);
                    float v = float(j + randf) / float(height);

                    Ray r = cam.GetRay(u, v);
                    color += Trace(r, lightList, scene, 0);
                }
                color /= float(aaSamples);
            }
            else {
                float u = float(i) / float(width);
                float v = float(j) / float(height);

                Ray r = cam.GetRay(u, v);
                color = Trace(r, lightList, scene, 0);
            }

            int red = int(color[0] * 255.99);
            int green = int(color[1] * 255.99);
            int blue = int(color[2] * 255.99);

            bufferedPixels[pixelNumber] = vec3(red, green, blue);
            pixelNumber++;

            if (pixelNumber == bucketSize) {
                writeBucketToFile(outputFile, bufferedPixels, bucketSize);
                pixelNumber = 0;
            }
        }
    }
    // Flush the rest
    if (pixelNumber != 0) {
        writeBucketToFile(outputFile, bufferedPixels, pixelNumber);
    }

    outputFile.close();
    clock_t end = clock();

    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::ostringstream oss;
    oss << "Elapsed time : " << elapsed_secs << "s";
    debug_log(oss.str());
}

