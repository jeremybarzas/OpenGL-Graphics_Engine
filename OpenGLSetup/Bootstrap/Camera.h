#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera
{
public:
	Camera();
	~Camera();
	void update(float);
	void setPerspective(float, float, float, float);
	void setLookat(vec3, vec3, vec3);
	void setPostion(vec3);
	mat4 getWorldTransform();
	mat4 getView();
	mat4 getProjection();
	mat4 getProjectionView();
	mat4 m_world;
	mat4 m_view;
	mat4 m_projection;
	mat4 m_projectionView;
	void updateProjectionViewTransform();
};

