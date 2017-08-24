#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

enum Axis
{
	ZAXIS,
	YAXIS,
	XAXIS,
};

class Transform
{	

public:
	Transform();
	~Transform();
	mat4 m_world; 
	mat4 m_local;
	mat4 m_rotation;
	mat4 m_positon;	

	void rotate(float radians, Axis rotationAxis);	
	void translate(vec3 trans);
};

