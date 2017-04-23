// rayK.cpp : Defines the entry point for the console application.

#define global_variable static

#include <windows.h>
#include "win32_rayK.h"

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <algorithm>

#include "vec3.h"
#include "Ray.h"
#include "Light.h"
#include "Camera.cpp"
#include "Raytracer.cpp"
#include "Scene.cpp"
#include "Sphere.cpp"
#include "Triangle.cpp"
#include "Lambert.cpp"

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


void Win32UpdateWindowCallback()
{
    HWND windowHandle = GetActiveWindow();
    RECT ClientRect;
    GetClientRect(windowHandle, &ClientRect);
    InvalidateRect(windowHandle, &ClientRect, true);
    UpdateWindow(windowHandle);
}


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
            SetBkMode(deviceContextHandle, TRANSPARENT);
            SetTextColor(deviceContextHandle, 0xFFFFFF);
            TextOut(deviceContextHandle, 10, 10, TEXT("Debug code"), 10);
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
    windowClass.hIcon = LoadIcon(windowInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    windowClass.lpszClassName = "rayKWindowClass";

    if (!RegisterClassA(&windowClass))
    {
        MessageBox(NULL,
                   "Call to RegisterClassEx failed!",
                   "Win32 Guided Tour",
                   NULL);
        return 1;
    }

    int res[2] = {400, 400};

    HWND windowHandle = CreateWindow(
        windowClass.lpszClassName,
        "rayK",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        // TODO(KK): check why windows won't draw this correctly without
        // enlarging the region
        int(res[0] * 1.2), int(res[1] * 1.2),
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
    Raytracer renderer = Raytracer();
    renderer.renderResolution[0] = res[0];
    renderer.renderResolution[1] = res[1];
    Win32InitBuffer(&backBuffer, res[0], res[1]);

    // Prepare the scene
    Scene sceneRoot = Scene();

    Camera cam = Camera(vec3(-2, 3, 5), vec3(0, 0, 0),
                        vec3(0, 1, 0), 50, float(res[0])/res[1], 3.5f);
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

    sceneRoot.AddObject(&sphr, 0);
    sceneRoot.AddObject(&sphr2, 1);
    sceneRoot.AddObject(&tri, 2);
    sceneRoot.AddObject(&tri2, 3);
    sceneRoot.AddObject(&plane, 4);

    Lambert mat = Lambert();
    sphr.pMat = &mat;
    sphr2.pMat = &mat;
    tri.pMat = &mat;
    tri2.pMat = &mat;
    plane.pMat = &mat;

    ShowWindow(windowHandle, showCode);
    UpdateWindow(windowHandle);

    renderer.Render(cam, lightList, sceneRoot, &backBuffer, Win32UpdateWindowCallback);

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
                renderer.Render(cam, lightList, sceneRoot, &backBuffer, Win32UpdateWindowCallback);
            }
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
    }
    return 0;
}

