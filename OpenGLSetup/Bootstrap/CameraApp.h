#pragma once
#include "Application.h"
#include "Camera.h"
#include "Gizmos.h"

class CameraApp :
	public Application
{
public:
	CameraApp();
	~CameraApp();

	// Inherited via Application
	virtual void startup() override;
	virtual void update(float) override;
	virtual void draw() override;
	virtual void shutdown() override;
		
	Camera* m_camera;
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
};

