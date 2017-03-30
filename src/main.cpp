// rayK.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <vector>
#include "vec3.h"
#include <algorithm>

#include "Camera.cpp"
#include "Logger.hpp"
#include "Scene.cpp"
#include "Sphere.cpp"
#include "Ray.cpp"
#include "Light.cpp"
#include "Object3d.cpp"
#include "Raytracer.cpp"
#include "Triangle.cpp"
#include "Lambert.cpp"

int main()
{
    debug_log("Start");
    Scene sceneRoot = Scene();

    Raytracer renderer = Raytracer();
    int res[2] = { 600, 400 };
    renderer.SetResolution(res);
    renderer.SetAASamples(32);

    const std::string outputFile = "C:\\Users\\krzykli\\kRay.ppm";

    Camera * cam = new Camera(vec3(-2, 3, 5), vec3(0, 0, 0),
                              vec3(0, 1, 0), 50, float(res[0])/res[1], 3.5f);
    cam -> SetName("Camera1");
    std::vector<Light> lightList;

    Sphere sphr(1);
    sphr.position = vec3(0, 0.5, 1);
    Sphere sphr2(1);
    sphr2.position = vec3(-1, 0.5, -2);

    Triangle tri(vec3(0, 1, 0), vec3(1.5, 0, 0), vec3(0, 0, 1));
    Triangle tri2(vec3(0, -1, -0.2f), vec3(-0.5f, 0.3f, 0), vec3(0, 0, 0));
    Triangle plane(vec3(100, 0, 100), vec3(-100, 0, 0), vec3(-100, 0, -100));

    Light lgt1 = Light();
    lgt1.position = vec3(2, 6, 5);
    lgt1.color = vec3(0, 1, 0);

    Light lgt2 = Light();
    lgt2.position = vec3(-2, 5, 0);
    lgt2.color = vec3(1, 0, 0);

    lightList.push_back(lgt1);
    lightList.push_back(lgt2);

    sceneRoot.AddObject(&sphr);
    sceneRoot.AddObject(&sphr2);
    sceneRoot.AddObject(&tri);
    sceneRoot.AddObject(&tri2);
    sceneRoot.AddObject(&plane);

    Lambert mat = Lambert();
    sphr.SetMaterial(&mat);
    sphr2.SetMaterial(&mat);
    tri.SetMaterial(&mat);
    tri2.SetMaterial(&mat);
    plane.SetMaterial(&mat);

    renderer.Render(*cam, lightList, sceneRoot, outputFile);

    return 0;
}

