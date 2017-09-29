#define GLM_FORCE_SWIZZLE
#include "Transform.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>



Transform::Transform() :
	m_world(1),
	m_local(1),
	m_rotation(1),
	m_scale(1),
	m_translation(1),
	World(m_world),
	Rotation(m_rotation),
	Translation(m_translation),
	Scale(m_scale),
	forward(World[2]),
	up(World[1]),
	right(World[0])
{}


Transform::~Transform() {}

void Transform::rotateAround(float radians, glm::vec3 axis)
{
	auto mMat = glm::angleAxis(radians, axis);
	m_world[0] = mMat * m_world[0];
	m_world[1] = mMat * m_world[1];
	m_world[2] = mMat * m_world[2];
}

void Transform::rotate(float radians, glm::vec3 axis)
{
	glm::vec3 x_Axis = glm::vec3(1, 0, 0);
	glm::vec3 y_Axis = glm::vec3(0, 1, 0);
	glm::vec3 z_Axis = glm::vec3(0, 0, 1);

	Axis rotationAxis = (axis == z_Axis) ? ZAXIS : (axis == y_Axis) ? YAXIS : XAXIS;

	auto cos = glm::cos(radians);
	auto sin = glm::sin(radians);

	switch (rotationAxis)
	{
	case ZAXIS:
		x_Axis = glm::vec3(cos, sin, 0);
		y_Axis = glm::vec3(-sin, cos, 0);
		z_Axis = glm::vec3(0, 0, 1);
		break;

	case YAXIS:
		x_Axis = glm::vec3(cos, 0, -sin);
		y_Axis = glm::vec3(0, 1, 0);
		z_Axis = glm::vec3(sin, 0, cos);
		break;

	case XAXIS:
		x_Axis = glm::vec3(1, 0, 0);
		y_Axis = glm::vec3(0, cos, sin);
		z_Axis = glm::vec3(0, -sin, cos);
		break;

	default:
		break;
	}

	auto rotation = glm::mat4(
		x_Axis.x, y_Axis.x, z_Axis.x, 0,
		x_Axis.y, y_Axis.y, z_Axis.y, 0,
		x_Axis.z, y_Axis.z, z_Axis.z, 0,
		0, 0, 0, 1
	);

	m_world = m_world * rotation;	
}

void Transform::translate(glm::vec3 trans)
{
	glm::mat4 translation = glm::mat4(1);
	// set w column of the new matrix4 to the transform that was passed in
	translation[3].x = trans.x;
	translation[3].y = trans.y;
	translation[3].z = trans.z;

	m_local = translation * m_rotation;
	m_world = m_world * m_local;
}

void Transform::setWorld(glm::mat4 world)
{
	m_world = world;
}

/*

| 00 04 08 12 |
| 01 05 09 13 |
| 02 06 10 14 |
| 03 07 11 15 |

[ 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 ]


*/