// rayK.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <vector>
#include "vec3.h"

#include "Camera.h"
#include "Logger.hpp"
#include "Scene.h"
#include "Sphere.h"
#include "Raytracer.h"
#include "Triangle.h"
#include <algorithm>
#include "Lambert.h"

int main()
{
    debug_log("Start");
    // Create scene root
    Scene sceneRoot = Scene();

    // Render Settings
    Raytracer renderer = Raytracer();
    int res[2] = { 600, 400 };
    renderer.SetResolution(res);
    renderer.SetAASamples(32);

    const std::string outputFile = "C:\\Users\\krzykli\\kRay.ppm";

    // Create render camera
    Camera * cam = new Camera(vec3(-2, 3, 5), vec3(0, 0, 0),
                              vec3(0, 1, 0), 50, float(res[0]/res[1]), 3.5f);
    cam -> SetName("Camera1");
    std::vector<Light> lightList;

    // Create geometry
    Sphere sphr(1);
    sphr.position = vec3(0, 0.5, 1);
    Sphere sphr2(1);
    sphr2.position = vec3(-1, 0.5, -2);

    Triangle tri(vec3(0, 1, 0), vec3(1.5, 0, 0), vec3(0, 0, 1));
    Triangle tri2(vec3(0, -1, -0.2f), vec3(-0.5f, 0.3f, 0), vec3(0, 0, 0));
    Triangle plane(vec3(100, 0, 100), vec3(-100, 0, 0), vec3(-100, 0, -100));

    // Create lights
    Light lgt1 = Light();
    lgt1.SetPosition(vec3(2, 6, 5));
    lgt1.SetColor(vec3(0, 1, 0));

    Light lgt2 = Light();
    lgt2.SetPosition(vec3(-2, 5, 0));
    lgt2.SetColor(vec3(1, 0, 0));

    lightList.push_back(lgt1);
    lightList.push_back(lgt2);

    // Add objects to the scene
    sceneRoot.AddObject(&sphr);
    sceneRoot.AddObject(&sphr2);
    sceneRoot.AddObject(&tri);
    sceneRoot.AddObject(&tri2);
    sceneRoot.AddObject(&plane);

    // Create and assign materials
    Lambert mat = Lambert();
    sphr.SetMaterial(&mat);
    sphr2.SetMaterial(&mat);
    tri.SetMaterial(&mat);
    tri2.SetMaterial(&mat);
    plane.SetMaterial(&mat);

    renderer.Render(*cam, lightList, sceneRoot, outputFile);

    return 0;
}

