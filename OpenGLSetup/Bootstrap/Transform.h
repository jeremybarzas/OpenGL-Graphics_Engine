#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>


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
	glm::mat4 m_world; 
	glm::mat4 m_local;
	glm::mat4 m_rotation;
	glm::vec3 m_positon;

	void rotate(float radians, Axis rotationAxis);	
	void translate(glm::vec3 trans);
};

