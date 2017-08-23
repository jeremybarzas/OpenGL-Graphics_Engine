#include "TestApp.h"
#include "Application.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <GLFW\glfw3.h>
#include "FlyCamera.h"

TestApp::TestApp()
{
}


TestApp::~TestApp()
{
}

void TestApp::startup()
{
	// initializes glfw
	glfwInit();

	// creates a Camera pointer and assigns it to new FlyCamera
	Camera* camera1 = new FlyCamera();
}

void TestApp::update(float deltaTime)
{
	// clears both the color and depth buffer so the window doesn't fail to update visuals
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TestApp::draw()
{
}

void TestApp::shutdown()
{
	// terminates glfw
	glfwTerminate();
}
