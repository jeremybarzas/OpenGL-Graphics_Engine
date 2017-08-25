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
	
	glm::mat4 m_translation;
	glm::mat4 m_rotation;
	glm::mat4 m_scale;
	glm::mat4 getWorld();
	glm::mat4 getRotation();
	glm::vec3 getPosition();

	void rotate(float radians, Axis rotationAxis);
	void translate(glm::vec3 trans);
	void setWorld(glm::mat4 world);

private:
	glm::mat4 m_world;	
};

