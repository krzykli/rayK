// rayK.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"	
#include <iostream>
#include <vector>

#include "Camera.h"
#include "Logger.hpp"
#include "Scene.h"
#include "Sphere.h"
#include "Raytracer.h"
#include "Triangle.h"
#include "Lambert.h"
#include "Readfile.h"


int main()
{
	debug_log("Start");
	// Create scene root
    Scene sceneRoot = Scene();

    // Render Settings
    Raytracer renderer = Raytracer();
    float res[2] = { 600, 300 };
    renderer.SetResolution(res);
    renderer.SetAASamples(2);

	const std::string outputFile = "C:\\Users\\krzykli\\kRay.ppm";

    // Create render camera
    Camera * cam = new Camera(vec3(-2, 3, 5), vec3(0, 0, 0), vec3(0, 1, 0), 50, res[0]/res[1], 3.5);
    cam -> SetName("Camera1");
    std::vector<Light> lightList;

 /*   std::vector<Object3d *> objects = readfile("C:\\Users\\krzykli\\ComputerGraphics\\raytracer\\hw3-submissionscenes\\smallTest.test");

    for (std::vector<Object3d *>::iterator it = objects.begin(); it != objects.end(); it++)
    {s
        sceneRoot.AddObject(*it);

        if (Camera* c = dynamic_cast<Camera*>(*it)) {
            cam = dynamic_cast<Camera*>(*it);
        }

        if (Light* lgt = dynamic_cast<Light*>(*it)) {
            lgt = dynamic_cast<Light*>(*it);
            lightList.push_back(*lgt);
        }

    }*/


    // Create geometry
    Sphere sphr(1);
    Transformation sphrTrans = sphr.GetTransform();
    sphrTrans.SetTranslate(vec3(0, 0.5, 1));
    sphr.SetTransform(sphrTrans);

    Sphere sphr2(1);
    Transformation sphrTrans2 = sphr2.GetTransform();
    sphrTrans2.SetTranslate(vec3(-1, 0.5, -2));
    sphr2.SetTransform(sphrTrans2);

    Sphere sphr3(1);
    Transformation sphrTrans3 = sphr3.GetTransform();
    sphrTrans3.SetTranslate(vec3(1, 0.5, -2));
    sphr3.SetTransform(sphrTrans3);

    Triangle tri(vec3(0, 1, 0), vec3(1.5, 0, 0), vec3(0, 0, 1));
    Triangle tri2(vec3(0, -1, -0.2), vec3(-0.5, 0.3, 0), vec3(0, 0, 0));
    Triangle plane(vec3(100, 0, 100), vec3(-100, 0, 0), vec3(-100, 0, -100));

    // Create lights


    Light lgt1 = Light();
    lgt1.SetColor(vec3(1, 0, 0));
    lgt1.SetPosition(vec3(2, 6, 5));

    Light lgt2 = Light();
    lgt2.SetColor(vec3(0, 1, 0));
    lgt2.SetPosition(vec3(-2, 5, 0));
    
    lightList.push_back(lgt1);
    lightList.push_back(lgt2);

    // Add objects to the scene
    sceneRoot.AddObject(&sphr);
    sceneRoot.AddObject(&sphr2);
    sceneRoot.AddObject(&sphr3);
    //sceneRoot.AddObject(&tri);
    //sceneRoot.AddObject(&tri2);
    sceneRoot.AddObject(&plane);

    // Create and assign materials
    Lambert mat = Lambert();
    sphr.SetMaterial(&mat);
    sphr2.SetMaterial(&mat);
    sphr3.SetMaterial(&mat);
    tri.SetMaterial(&mat);
    tri2.SetMaterial(&mat);
    plane.SetMaterial(&mat);


	renderer.Render(*cam, lightList, sceneRoot, outputFile);

	debug_log("End");
    return 0;
}

