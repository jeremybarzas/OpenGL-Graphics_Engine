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

	void rotateAround(float radians, glm::vec3 axis);

	void rotate(float radians, glm::vec3 axis);
	void translate(glm::vec3 trans);
	void setWorld(glm::mat4 world);

	const glm::mat4& World;
	const glm::mat4& Translation;
	const glm::mat4& Rotation;
	const glm::mat4& Scale;
	const glm::vec4& forward;
	const glm::vec4& up;
	const glm::vec4& right;
private:
	
	glm::mat4 m_world;
	glm::mat4 m_local;
	glm::mat4 m_translation;
	glm::mat4 m_rotation;
	glm::mat4 m_scale;
};
