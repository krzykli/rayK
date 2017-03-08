#ifndef VEC3H
#define VEC3H

#include <stdio.h>
#include <math.h>
#include <iostream>

struct vec3
{
    float v[3];

    float x;
    float y;
    float z;

    vec3()
    {}

    vec3(float x, float y, float z):
        x(x),
        y(y),
        z(z)
    {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }

    vec3(float x):
        x(x),
        y(x),
        z(x)
    {
        v[0] = x;
        v[1] = x;
        v[2] = x;
    }

    // Unary operators
    vec3& operator+= (vec3& v)
    {
         x = x + v.x;
         y = y + v.y;
         z = z + v.z;
         return *this;
    }

    vec3& operator-= (float s)
    {
         x = x - s;
         y = y - s;
         z = z - s;
         return *this;
    }

    vec3& operator- ()
    {
         return vec3(-x, -y, -z);
    }

    vec3& operator*= (float s)
    {
         x = x * s;
         y = y * s;
         z = z * s;
         return *this;
    }

    vec3& operator/= (float s)
    {
         x = x * 1 / s;
         y = y * 1 / s;
         z = z * 1 / s;
         return *this;
    }

    vec3& operator= (const vec3& v)
    {
         x = v.x;
         y = v.y;
         z = v.z;
         return *this;
    }

    float operator[] (int i)
    {
         return v[i];
    }

    void show()
    {
        printf("<%f, %f, %f>\n", this->x, this->y, this->z);
    }

    float length()
    {
        return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
    }

    static float dot(const vec3& v1, const vec3& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    static vec3 cross(const vec3& v1, const vec3& v2)
    {
        return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

    static vec3 normalize(const vec3& v)
    {
        float a = 1.0 / sqrt(pow(v.x, 2) + pow(v.x, 2) + pow(v.x, 2));
        return vec3(v.x * a, v.y * a, v.z * a);
    }

    static vec3 min(const vec3& v1, const vec3& v2)
    {
        float a = v1.x > v2.x ? v1.x : v2.x;
        float b = v1.y > v2.y ? v1.y : v2.y;
        float c = v1.z > v2.z ? v1.z : v2.z;
        return vec3(a, b, c);
    }
};

inline vec3 operator+ (const vec3& v1, const vec3& v2)
{
     return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline vec3 operator- (const vec3& v1, const vec3& v2)
{
     return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline vec3 operator* (const vec3& v1, const vec3& v2)
{
     return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline vec3 operator* (const vec3& v, float s)
{
     return vec3(v.x * s, v.y * s, v.z * s);
}

inline vec3 operator* (float s, const vec3& v)
{
     return vec3(v.x * s, v.y * s, v.z * s);
}

inline vec3 operator/ (const vec3& v, float s)
{
     return vec3(v.x / s, v.y / s, v.z / s);
}

inline std::istream& operator>> (std::istream& is, vec3& v)
{
    is >> v.x >> v.y >> v.z;
    return is;
}

inline std::ostream& operator<< (std::ostream& os, vec3& v)
{
    os << v.x << " " << v.y  << " " << v.z;
    return os;
}

#endif // VEC3H
