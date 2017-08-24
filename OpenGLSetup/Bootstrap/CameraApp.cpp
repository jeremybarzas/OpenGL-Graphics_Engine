#include "CameraApp.h"
using glm::pi;


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

	m_camera->setLookat(eye, center, up);
	m_camera->setPerspective(pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);	
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
	
	// removes all shapes and lines from the buffer
	Gizmos::clear();

	// creates transform handles
	Gizmos::addTransform(glm::mat4(1));

	// colors to be used
	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	// generates a grid of lines
	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}
}

void CameraApp::draw()
{	
	Gizmos::draw(m_camera->m_projectionView);
}

void CameraApp::shutdown()
{
	Gizmos::destroy();
}
