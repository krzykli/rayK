// rayK.cpp : Defines the entry point for the console application.

#define global_variable static

#include <windows.h>

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
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
#include "Triangle.cpp"
#include "Lambert.cpp"

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;


struct win32_offscreen_buffer
{
    BITMAPINFO Info;
    void *Memory;
    int Width;
    int Height;
    int Pitch;
};


struct win32_window_dimension
{
    int Width;
    int Height;
};


global_variable win32_offscreen_buffer backBuffer;
global_variable bool isRunning;

global_variable int redOffset = 0;
global_variable int greenOffset = 0;
global_variable int blueOffset = 0;


static void
Win32InitBuffer(win32_offscreen_buffer *buffer, int width, int height)
{
    if(buffer->Memory)
    {
        VirtualFree(buffer->Memory, 0, MEM_RELEASE);
    }

    buffer->Width = width;
    buffer->Height = height;

    int BytesPerPixel = 4;

    buffer->Info.bmiHeader.biSize = sizeof(buffer->Info.bmiHeader);
    buffer->Info.bmiHeader.biWidth = buffer->Width;
    buffer->Info.bmiHeader.biHeight = -buffer->Height;
    buffer->Info.bmiHeader.biPlanes = 1;
    buffer->Info.bmiHeader.biBitCount = 32;
    buffer->Info.bmiHeader.biCompression = BI_RGB;

    int BitmapMemorySize = (buffer->Width * buffer->Height) * BytesPerPixel;
    buffer->Memory = VirtualAlloc(0, BitmapMemorySize, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    buffer->Pitch = width * BytesPerPixel;
}


static win32_window_dimension
Win32GetWindowDimension(HWND Window)
{
    win32_window_dimension Result;

    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    Result.Width = ClientRect.right - ClientRect.left;
    Result.Height = ClientRect.bottom - ClientRect.top;

    return(Result);
}


static void
Win32DisplayBufferInWindow(win32_offscreen_buffer *Buffer,
                           HDC DeviceContext, int WindowWidth, int WindowHeight)
{
    StretchDIBits(DeviceContext,
                  0, 0, WindowWidth, WindowHeight,
                  0, 0, Buffer->Width, Buffer->Height,
                  Buffer->Memory,
                  &Buffer->Info,
                  DIB_RGB_COLORS, SRCCOPY);
}


struct Raytracer {
    int renderResolution[2] = {800, 450};
    int aaSamples = 0;
    int rayDepth = 5;

    vec3 Raytracer::Trace(
        const Ray& r, std::vector<Light*>& lightList, Scene& scene, int depth)
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

    void Raytracer::Render(
            Camera &cam,
            std::vector<Light*> & lightList,
            Scene &scene,
            win32_offscreen_buffer *Buffer)
    {
        clock_t begin = clock();

        uint32 *Pixel = (uint32 *)Buffer->Memory;
        for(int i = Buffer->Height; i >=0; --i)
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

            HWND windowHandle = GetActiveWindow();
            HDC deviceContextHandle = GetDC(windowHandle);
            win32_window_dimension Dimension = Win32GetWindowDimension(windowHandle);
            Win32DisplayBufferInWindow(&backBuffer, deviceContextHandle,
                                       Dimension.Width, Dimension.Height);
        }

        clock_t end = clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        printf("%f", elapsed_secs);
    }
};


LRESULT CALLBACK
Win32WindowCallback(HWND windowHandle,
                    UINT message,
                    WPARAM wParam,
                    LPARAM lParam)
{
    LRESULT result = 0;

    switch (message)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT paintStruct;
            HDC deviceContextHandle;
            deviceContextHandle = BeginPaint(windowHandle, &paintStruct);
            win32_window_dimension Dimension = Win32GetWindowDimension(windowHandle);
            Win32DisplayBufferInWindow(&backBuffer, deviceContextHandle,
                                       Dimension.Width, Dimension.Height);

            EndPaint(windowHandle, &paintStruct);
        } break;

        case WM_DESTROY:
        {
            isRunning = false;
            DestroyWindow(windowHandle);
        } break;

        default:
        {
            return DefWindowProc(windowHandle, message, wParam, lParam);
        }
    }
    return(result);
}


int CALLBACK WinMain(HINSTANCE windowInstance,
                     HINSTANCE prevInstance,
                     LPSTR     commandLine,
                     int       showCode)
{
    WNDCLASSA windowClass = {};
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = Win32WindowCallback;
    windowClass.hInstance = windowInstance;
    windowClass.lpszClassName = "rayKWindowClass";

    if (!RegisterClassA(&windowClass))
    {
        MessageBox(NULL,
                   "Call to RegisterClassEx failed!",
                   "Win32 Guided Tour",
                   NULL);
        return 1;
    }

    HWND windowHandle = CreateWindow(
        windowClass.lpszClassName,
        "rayK",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        windowInstance,
        NULL);

    if (!windowHandle)
    {
        MessageBox(NULL,
                   "Call to CreateWindow failed!",
                   "Win32 Error",
                   NULL);
        return 1;
    }

    isRunning = true;
    Win32InitBuffer(&backBuffer, 800, 450);

    // Prepare the scene
    debug_log("Start");
    Scene sceneRoot = Scene();

    Raytracer renderer = Raytracer();
    int res[2] = {800, 450};
    renderer.renderResolution[0] = res[0];
    renderer.renderResolution[1] = res[1];

    Camera cam = Camera(vec3(-2, 3, 5), vec3(0, 0, 0),
                        vec3(0, 1, 0), 50, float(res[0])/res[1], 3.5f);
    cam.SetName("Camera1");
    std::vector<Light*> lightList;

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

    lightList.push_back(&lgt1);
    lightList.push_back(&lgt2);

    sceneRoot.AddObject(&sphr);
    sceneRoot.AddObject(&sphr2);
    sceneRoot.AddObject(&tri);
    sceneRoot.AddObject(&tri2);
    sceneRoot.AddObject(&plane);

    Lambert mat = Lambert();
    sphr.pMat = &mat;
    sphr2.pMat = &mat;
    tri.pMat = &mat;
    tri2.pMat = &mat;
    plane.pMat = &mat;

    while (isRunning)
    {
        MSG message;
        while(PeekMessage(&message, 0, 0, 0, PM_REMOVE))
        {
            if(message.message == WM_QUIT)
            {
                isRunning = false;
                PostQuitMessage(0);
            }
            else if(message.message == WM_KEYUP)
            {
                WPARAM VK_CODE = message.wParam;
                vec3 currentLightPosition = lightList[0]->position;
                if(VK_CODE == VK_ESCAPE)
                {
                    isRunning = false;
                }
                else if(VK_CODE == VK_LEFT)
                {
                    lightList[0]->position.v[0] = currentLightPosition.x() - 1;
                }
                else if(VK_CODE == VK_RIGHT)
                {
                    lightList[0]->position.v[0] = currentLightPosition.x() + 1;
                }
                else if(VK_CODE == VK_UP)
                {
                    lightList[0]->position.v[1] = currentLightPosition.y() + 1;
                }
                else if(VK_CODE == VK_DOWN)
                {
                    lightList[0]->position.v[1] = currentLightPosition.y() - 1;
                }
            }
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }

        ShowWindow(windowHandle, showCode);
        UpdateWindow(windowHandle);
        renderer.Render(cam, lightList, sceneRoot, &backBuffer);

        HDC deviceContextHandle = GetDC(windowHandle);
        win32_window_dimension Dimension = Win32GetWindowDimension(windowHandle);
        Win32DisplayBufferInWindow(&backBuffer, deviceContextHandle,
                                   Dimension.Width, Dimension.Height);
    }

    return 0;
}

