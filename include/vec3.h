#ifndef VEC3H
#define VEC3H

#include <stdio.h>
#include <math.h>
#include <iostream>

struct vec3
{
    float v[3];

    vec3()
    {}

    vec3(float x, float y, float z)
    {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }

    vec3(float x)
    {
        v[0] = x;
        v[1] = x;
        v[2] = x;
    }

    float x()
    {
        return v[0];
    }

    float y()
    {
        return v[1];
    }

    float z()
    {
        return v[2];
    }

    // Unary operators
    vec3& operator+= (vec3& v1)
    {
         v[0] = v[0] + v1[0];
         v[1] = v[1] + v1[1];
         v[2] = v[2] + v1[2];
         return *this;
    }

    vec3& operator-= (float s)
    {
         v[0] = v[0] - s;
         v[1] = v[1] - s;
         v[2] = v[2] - s;
         return *this;
    }

    vec3& operator- ()
    {
         v[0] = -v[0];
         v[1] = -v[1];
         v[2] = -v[2];
         return *this;
    }

    vec3& operator*= (float s)
    {
         v[0] = v[0] * s;
         v[1] = v[1] * s;
         v[2] = v[2] * s;
         return *this;
    }

    vec3& operator/= (float s)
    {
         v[0] = v[0] / s;
         v[1] = v[1] / s;
         v[2] = v[2] / s;
         return *this;
    }

    float operator[] (int i)
    {
         return v[i];
    }

    float operator[] (int i) const
    {
         return v[i];
    }

    void show()
    {
        printf("<%f, %f, %f>\n", v[0], v[1], v[2]);
    }

    float length()
    {
        return sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2));
    }

    static float dot(const vec3 &v1, const vec3 &v2) {
        return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    }

    static vec3 normalize(const vec3& v1)
    {
        float a = 1.0f / sqrt(pow(v1[0], 2) + pow(v1[1], 2) + pow(v1[2], 2));
        return vec3(v1[0] * a, v1[1] * a, v1[2] * a);
    }

    static vec3 cross(const vec3 &v1, const vec3 &v2) {
        return vec3((v1[1] * v2[2] - v1[2] * v2[1]),
                    (-(v1[0] * v2[2] - v1[2] * v2[0])),
                    (v1[0] * v2[1] - v1[1] * v2[0]));
    }

    static vec3 min(const vec3& v1, const vec3& v2)
    {
        float a = v1[0] > v2[0] ? v2[0] : v1[0];
        float b = v1[1] > v2[1] ? v2[1] : v1[1];
        float c = v1[2] > v2[2] ? v2[2] : v1[2];
        return vec3(a, b, c);
    }
};

inline vec3 operator+ (const vec3& v1, const vec3& v2)
{
     return vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

inline vec3 operator- (const vec3& v1, const vec3& v2)
{
     return vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

inline vec3 operator* (const vec3& v1, const vec3& v2)
{
     return vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline vec3 operator* (const vec3& v1, float s)
{
     return vec3(v1[0] * s, v1[1] * s, v1[2] * s);
}

inline vec3 operator* (float s, const vec3& v1)
{
     return v1 * s;
}

inline vec3 operator/ (const vec3& v1, float s)
{
     return vec3(v1[0] / s, v1[1] / s, v1[2] / s);
}

inline std::istream& operator>> (std::istream& is, const vec3& v1)
{
    is >> v1[0] >> v1[1] >> v1[2];
    return is;
}

inline std::ostream& operator<< (std::ostream& os, const vec3& v1)
{
    os << v1[0] << " " << v1[1]  << " " << v1[2];
    return os;
}

#endif // VEC3H
