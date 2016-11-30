#include "stdafx.h"
#include "Triangle.h"

#define EPSILON 0.000001

Triangle::Triangle(vec3 verts[3])
{
    m_verts[0] = verts[0];
    m_verts[1] = verts[1];
    m_verts[2] = verts[2];
    m_A = m_verts[0];
    m_B = m_verts[1];
    m_C = m_verts[2];
    m_normal = -normalize(cross(m_B - m_A, m_C - m_A));
}

Triangle::Triangle(vec3 & a, vec3 & b, vec3 & c)
{
    m_verts[0] = a;
    m_verts[1] = b;
    m_verts[2] = c;
    m_A = a;
    m_B = b;
    m_C = c;
    m_normal = -normalize(cross(m_B - m_A, m_C - m_A));
}


bool Triangle::hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const 
{
    float u, v, distance;

    vec3 AB = (m_B - m_A);
    vec3 AC = (m_C - m_A);
    vec3 normal = normalize(cross(AC, AB));

    vec3 rayCrossEdge = cross(ray.GetDirection(), AC);

    float det = dot(AB, rayCrossEdge);

    if (det > -EPSILON && det < EPSILON)
        return 0;

    float inv_det = 1.0 / det;

    vec3 rayToVert = ray.GetOrigin() - m_A;
    u = dot(rayToVert, rayCrossEdge) * inv_det;
    if (u < 0.0 || u > 1.0)
        return 0;

    vec3 qvec = cross(rayToVert, AB);
    v = dot(ray.GetDirection(), qvec) * inv_det;
    if (v < 0.0 || u + v > 1.0)
        return 0;

    distance = dot(AC, qvec) * inv_det;
    if (distance > t_min && distance < t_max) {
        rec.p = ray.PointAtDistance(distance);
        rec.normal = m_normal;
        rec.t = distance;
        rec.pMat = GetMaterial();
        return true;
    }

    return false;
}