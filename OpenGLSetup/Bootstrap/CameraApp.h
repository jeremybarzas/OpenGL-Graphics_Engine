#pragma once
#include "Application.h"
#include "Camera.h"
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
	vec3 eye;
	vec3 center;
	vec3 up;
};

