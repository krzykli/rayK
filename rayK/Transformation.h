#pragma once
#include <stack>
#include "glm\glm.hpp"

using namespace glm;

class Transformation
{
public:
	Transformation();

	~Transformation();
	
	mat4 GetMatrix4() const;

	void SetMatrix4(const mat4 &in_matrix);

	void SetScale(const vec3 &s);

	void SetRotateAroundAxis(const float degrees, const vec3 &axis);

    void SetRotateX(const float degrees);

    void SetRotateY(const float degrees);

    void SetRotateZ(const float degrees);

    void SetRotateXYZ(const vec3 & rot);

	void SetTranslate(const vec3 &t);

	vec3 GetTranslation() const;

private:
	mat4 m_rotation;
	mat4 m_translation;
	mat4 m_scale;
	mat4 m_xform;
};

