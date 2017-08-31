#define GLM_FORCE_SWIZZLE
#include "Transform.h"



Transform::Transform() : m_world(1), m_rotation(1), m_scale(1)
{
}


Transform::~Transform()
{
}

glm::mat4 Transform::getWorld()
{
	return m_world;
}
glm::mat4 Transform::getRotation()
{
	return glm::extractMatrixRotation(m_world);
}
glm::vec3 Transform::getPosition()
{
	return m_world[3].xyz;
}

void Transform::rotate(float radians, Axis rotationAxis)
{
	glm::vec3 xAxis = glm::vec3(1, 0, 0);
	glm::vec3 yAxis = glm::vec3(0, 1, 0);
	glm::vec3 zAxis = glm::vec3(0, 0, 1);

	glm::vec3 rotaxis = (rotationAxis == ZAXIS) ? glm::vec3(0, 0, 1) 
				: (rotationAxis == YAXIS) ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0);

	switch(rotationAxis)
	{
	case ZAXIS:
		xAxis = glm::vec3(glm::cos(radians), glm::sin(radians), 0);
		yAxis = glm::vec3(-glm::sin(radians), glm::cos(radians), 0);
		zAxis = glm::vec3(0, 0, 1);
		break;

	case YAXIS:
		xAxis = glm::vec3(glm::cos(radians), 0, -glm::sin(radians));
		yAxis = glm::vec3(0, 1, 0);
		zAxis = glm::vec3(glm::sin(radians), 0, glm::cos(radians));
		break;

	case XAXIS:
		xAxis = glm::vec3(1, 0, 0);
		yAxis = glm::vec3(0, glm::cos(radians), glm::sin(radians));
		zAxis = glm::vec3(0, -glm::sin(radians), glm::cos(radians));
		break;

	default: 
		break;
	}

	m_rotation = glm::mat4(
		glm::vec4(xAxis, 1),
		glm::vec4(yAxis, 1),
		glm::vec4(zAxis, 1),
		glm::vec4(0, 0, 0, 1)
	);

	m_world = m_translation = m_rotation;
}

void Transform::translate(glm::vec3 trans)
{ 
	// set w column of the new matrix4 to the transform that was passed in
	m_translation[3].x += trans.x;
	m_translation[3].y += trans.y;
	m_translation[3].z += trans.z;

	m_world = m_translation * m_rotation;	
}

void Transform::setWorld(glm::mat4 world)
{
	m_translation[3]= world[3];
	m_rotation = glm::extractMatrixRotation(world);
}

