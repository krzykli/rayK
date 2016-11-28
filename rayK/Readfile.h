#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Object3d.h"
#include "Camera.h"
#include "Triangle.h"


bool readvals(std::stringstream &s, const int numvals, float* values)
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i];
        if (s.fail()) {
            std::cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

std::vector<Object3d *> readfile(const char* filename)
{
    std::string str, cmd;
    std::ifstream in;

    std::vector<Object3d *> objects;
    std::vector<vec3> vertices;

    float sizeX;
    float sizeY;

    in.open(filename);
    if (in.is_open()) {
        getline(in, str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines 

                std::stringstream s(str);
                s >> cmd;
                int i;
                bool validinput; // Validity of input 
                float values[10];

                if (cmd == "size") {
                    validinput = readvals(s, 2, values);
                    if (validinput) {
                        sizeX = values[0];
                        sizeY = values[1];
                    }
                }

                if (cmd == "camera") {        
                    validinput = readvals(s, 10, values);
                    if (validinput) {
                        vec3 pos(values[0], values[1], values[2]);
                        vec3 lookAt(values[3], values[4], values[5]);
                        vec3 upV(values[6], values[7], values[8]);
                        float fovy = values[9];
                        float aspectRatio = 1.0;
                        Camera * cam = new Camera(pos, lookAt, upV, fovy, sizeX/sizeY, 3);
                        objects.push_back(cam);
                    }
                }

                if (cmd == "point") {
                    validinput = readvals(s, 6, values);
                    if (validinput) {
                        vec3 pos(values[0], values[1], values[2]);
                        vec3 color(values[3], values[4], values[5]);
                        Light * lgt = new Light();
                        lgt->SetPosition(pos);
                        lgt->SetColor(color);
                        objects.push_back(lgt);
                    }
                }

                if (cmd == "vertex") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        vertices.push_back(vec3(values[0], values[1], values[2]));
                    }
                }

                if (cmd == "tri") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        vec3 verts[3] = { vertices[values[0]], vertices[values[1]], vertices[values[2]] };
                        Triangle * tri = new Triangle(verts);
                        objects.push_back(tri);
                    }
                }
            }
            getline(in, str);
        }
    }
    else {
        std::cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }

    return objects;
}