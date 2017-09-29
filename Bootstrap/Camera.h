#pragma once
#include <glm\mat4x4.hpp>
#include "Transform.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void update(float deltaTime);
	void setPerspective(float fieldOfView, float aspectRatio, float near, float far);	
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setOrthographic(float left, float right, float bottom, float top, float near, float far);
	void setProjection(bool perspective);
	
	
	Transform& transform;
	glm::mat4& view;
	glm::mat4& projection; 
	glm::mat4& projectionView;
	float m_fov;
	float m_aspectRatio;
	float m_near;
	float m_far;
	float m_top;
	float m_bottom;
	float m_left;
	float m_right;	

private:

	Transform m_transform;
	glm::mat4 m_world;
	glm::mat4 m_view;
	glm::mat4 m_projection;	
	glm::mat4 m_projectionView;
	glm::vec3 m_target;
	glm::vec3 m_up;
	float m_speed;
};
