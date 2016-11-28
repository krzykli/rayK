#pragma once
#include "stdafx.h"	
#include "Ray.h"

Ray::Ray(const vec3 & origin, const vec3 & direction) :
    m_origin(origin),
    m_direction(direction)
{}

vec3 Ray::GetOrigin() const {
	return m_origin;
}

vec3 Ray::GetDirection() const {
	return m_direction;
}

vec3 Ray::PointAtDistance(float t) const {
	return m_origin + t * m_direction;
}