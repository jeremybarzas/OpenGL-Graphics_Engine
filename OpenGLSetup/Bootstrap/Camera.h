#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>
using glm::mat4;
using glm::vec3;

class Camera
{
public:
	Camera();
	virtual ~Camera();
	virtual void update(float) = 0;
	virtual void setPerspective(float, float, float, float) = 0;
	virtual void setLookat(vec3, vec3, vec3) = 0;
	virtual void setPostion(vec3) = 0;
	virtual mat4 getWorldTransform();
	virtual mat4 getView();
	virtual mat4 getProjection();
	virtual mat4 getProjectionView();

private:
	mat4 worldTransform;
	mat4 viewTransform;
	mat4 projectionTransform;
	mat4 projectionViewTransform;
	virtual void updateProjectionViewTransform();
};

