#include "CameraApp.h"



CameraApp::CameraApp()
{
}


CameraApp::~CameraApp()
{
}

void CameraApp::startup()
{	
	m_camera = new Camera();
	eye = vec3(10, 10, 10);
	center = vec3(0);
	up = vec3(0, 1, 0);
}

void CameraApp::update(float deltaTime)
{	
	//camera forward
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		m_camera->m_world;
	}	

	//camera left
	if (glfwGetKey(window, GLFW_KEY_A))
	{

	}

	//camera backward
	if (glfwGetKey(window, GLFW_KEY_S))
	{

	}

	//camera right
	if (glfwGetKey(window, GLFW_KEY_D))
	{

	}

	m_camera->setLookat(eye, center, up);
}

void CameraApp::draw()
{
}

void CameraApp::shutdown()
{
}
