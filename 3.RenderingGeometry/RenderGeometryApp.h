#pragma once
#include <Application.h>
#include "Camera.h"
#include "Gizmos.h"
#include "Mesh.h"


class RenderGeometryApp : public Application
{
public:
	RenderGeometryApp();
	~RenderGeometryApp();	

	// Inherited via Application
	virtual void startup() override;
	virtual void update(float) override;
	virtual void draw() override;
	virtual void shutdown() override;

	Camera* m_camera;
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;	

	Mesh* m_mesh;
};

