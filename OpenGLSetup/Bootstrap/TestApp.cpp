#include "TestApp.h"
#include "Application.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <GLFW\glfw3.h>

TestApp::TestApp()
{
}


TestApp::~TestApp()
{
}

void TestApp::startup()
{
	
}

void TestApp::update(float deltaTime)
{	
	// changes the clear color to red if 'r' is pressed
	if (glfwGetKey(m_window, GLFW_KEY_R))
		glClearColor(1, 0, 0, 1);

	// change the clear color to green if 'g' is pressed
	if (glfwGetKey(m_window, GLFW_KEY_G))
		glClearColor(0, 1, 0, 1);

	// change the clear color to blue if 'b' is pressed
	if (glfwGetKey(m_window, GLFW_KEY_B))
		glClearColor(0, 0, 1, 1);

	// change the clear color to grey if "space" is pressed
	if (glfwGetKey(m_window, GLFW_KEY_SPACE))
		glClearColor(0.5f, 0.5f, 0.5f, 1);
}

void TestApp::draw()
{
}

void TestApp::shutdown()
{
	
}
