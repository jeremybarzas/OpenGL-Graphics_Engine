#include "Transform.h"



Transform::Transform() : m_local(1), m_world(1), m_rotation(1), m_positon(1)
{
}


Transform::~Transform()
{
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

	m_world = m_rotation;

	//glm::mat4 test = glm::rotate(radians, rotaxis);
	//assert(m_rotation == test);
}

void Transform::translate(glm::vec3 trans)
{
	// creates a new matrix4 that is the identity matrix
	glm::mat4 translation = glm::mat4(1);

	// set w column of the new matrix4 to the transform that was passed in
	translation[3].x = trans.x;
	translation[3].y = trans.y;
	translation[3].z = trans.z;

	// apply the new translation to the world transform
	m_world = m_world * translation;

	// assert to test against glm's translate funtion
	glm::mat4 test = glm::translate(trans);
	assert(m_world == test);
}

