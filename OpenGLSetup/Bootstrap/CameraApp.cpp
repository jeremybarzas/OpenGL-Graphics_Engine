#include "CameraApp.h"



CameraApp::CameraApp()
{
}


CameraApp::~CameraApp()
{
}

void CameraApp::startup()
{
}

void CameraApp::update(float)
{
	Camera* testcam = new Camera();

	const vec3 eye = vec3(10, 10, 10);
	const vec3 center = vec3(0);
	const vec3 up = vec3(0, 1, 0);

	testcam->setLookat(eye, center, up);
}

void CameraApp::draw()
{
}

void CameraApp::shutdown()
{
}
