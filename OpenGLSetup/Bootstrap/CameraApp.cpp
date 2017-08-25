#include "CameraApp.h"
using glm::pi;
#include <iostream>


CameraApp::CameraApp()
{
}


CameraApp::~CameraApp()
{
}

void CameraApp::startup()
{		
	// camera object initialization
	m_camera = new Camera();	

	// sets the view and world transforms of the camera
	eye = glm::vec3(10, 10, 10);
	center = glm::vec3(0);
	up = glm::vec3(0, 1, 0);
	m_camera->setLookat(eye, center, up);

	// sets the perspective view of the camera
	m_camera->setPerspective(pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
}

void CameraApp::update(float deltaTime)
{	
	// camera strafe forward
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{	
		// calculate the forward vector of the cameras current rotation		

		// apply movement along forward vector scaled by deltatime / multiplier
	}

	// camera strafe backward
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
				
	}

	// camera strafe left
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		
	}	

	// camera strafe right
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		
	}	

	// gets mouse input	
	static bool mouseButtonDown = false;
	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {

		static double prevMouseX = 0;
		static double PrevMouseY = 0;

		if (mouseButtonDown == false)
		{
			mouseButtonDown = true;
			glfwGetCursorPos(m_window, &prevMouseX, &PrevMouseY);
		}

		double currMouseX = 0;
		double currMouseY = 0;
		glfwGetCursorPos(m_window, &currMouseX, &currMouseY);

		double deltaX = currMouseX - prevMouseX;
		double deltaY = currMouseY - PrevMouseY;

		prevMouseX = currMouseX;
		PrevMouseY = currMouseY;
		std::cout << "delta mouse:: " << glm::to_string(glm::vec2(deltaX, deltaY)) << "\n";
	}	
}

void CameraApp::draw()
{	
	// removes all shapes and lines from the buffer
	Gizmos::clear();

	// creates transform handles
	Gizmos::addTransform(glm::mat4(1));

	// colors to be used
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);

	// generates a grid of lines
	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
			glm::vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		Gizmos::addLine(glm::vec3(10, 0, -10 + i),
			glm::vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}
	
	// what is current in the gizmos buffer
	Gizmos::draw(m_camera->m_projectionView);
}

void CameraApp::shutdown()
{
	// destroys the gizmos object
	Gizmos::destroy();
}
