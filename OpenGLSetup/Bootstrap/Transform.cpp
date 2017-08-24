#include "Transform.h"



Transform::Transform() : m_local(1), m_world(1), m_rotation(1), m_positon(1)
{
}


Transform::~Transform()
{
}

void Transform::rotate(float radians, Axis rotationAxis)
{
	vec3 xAxis = vec3(1, 0, 0);
	vec3 yAxis = vec3(0, 1, 0);
	vec3 zAxis = vec3(0, 0, 1);

	vec3 rotaxis = (rotationAxis == ZAXIS) ? vec3(0, 0, 1) 
		: (rotationAxis == YAXIS) ? vec3(0, 1, 0) : vec3(1, 0, 0);

	switch(rotationAxis)
	{
	case ZAXIS:
		xAxis = vec3(cos(radians), sin(radians), 0);
		yAxis = vec3(-sin(radians), cos(radians), 0);
		zAxis = vec3(0, 0, 1);
		break;

	case YAXIS:
		xAxis = vec3(cos(radians), 0, -sin(radians));
		yAxis = vec3(0, 1, 0);
		zAxis = vec3(sin(radians), 0, cos(radians));
		break;

	case XAXIS:
		xAxis = vec3(1, 0, 0);
		yAxis = vec3(0, cos(radians), sin(radians));
		zAxis = vec3(0, -sin(radians), cos(radians));
		break;

	default: 
		break;
	}

	m_rotation = mat4(
		vec4(xAxis, 1),
		vec4(yAxis, 1),
		vec4(zAxis, 1),
		vec4(0, 0, 0, 1)
	);

	m_world = m_rotation;

	mat4 test = glm::rotate(radians, rotaxis);
	assert(m_rotation == test);
}

void Transform::translate(vec3 trans)
{
	// creates a new matrix4 that is the identity matrix
	mat4 translation = mat4(1);

	// set w column of the new matrix4 to the transform that was passed in
	translation[3].x = trans.x;
	translation[3].y = trans.y;
	translation[3].z = trans.z;

	// apply the new translation to the world transform
	m_world = m_world * translation;

	// assert to test against glm's translate funtion
	mat4 test = glm::translate(trans);
	assert(m_world == test);
}

