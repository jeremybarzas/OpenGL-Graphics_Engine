#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include "Transform.h"

class Camera
{
public:
	Camera();
	~Camera();
	void update(float);
	void updateProjectionViewTransform();
	void setPerspective(float, float, float, float);
	void setLookat(glm::vec3, glm::vec3, glm::vec3);
	void setPostion(glm::vec3);
	glm::mat4 getWorldTransform();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionView();		

	glm::mat4 m_world;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::mat4 m_projectionView;

	Transform* m_transform;	
};

