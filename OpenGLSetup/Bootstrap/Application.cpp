#include "Application.h"
#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>

Application::Application()
{
}


Application::~Application()
{
}

void inputcheck(GLFWwindow* window)
{
	// sets the loop condition to true if "escape" is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, GL_TRUE);

	// changes the clear color to red if 'r' is pressed
	if (glfwGetKey(window, GLFW_KEY_R))
		glClearColor(1, 0, 0, 1);

	// change the clear color to green if 'g' is pressed
	if (glfwGetKey(window, GLFW_KEY_G))
		glClearColor(0, 1, 0, 1);

	// change the clear color to blue if 'b' is pressed
	if (glfwGetKey(window, GLFW_KEY_B))
		glClearColor(0, 0, 1, 1);

	// change the clear color to grey if "space" is pressed
	if (glfwGetKey(window, GLFW_KEY_SPACE))
		glClearColor(0.5f, 0.5f, 0.5f, 1);
}

void Application::run(float width, float height, const char * title, bool fullscreen)
{
	// calls the concrete derived class startup() method
	startup();	

	// creates a window to draw in with OpenGL
	GLFWmonitor* monitor;
	fullscreen == false ? monitor = nullptr : monitor = glfwGetPrimaryMonitor();
	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, nullptr);

	// makes the pased in window the current context
	glfwMakeContextCurrent(window);

	// loads all of the OpenGL extenstions
	ogl_LoadFunctions();

	// set window clear color to grey
	glClearColor(0.5f, 0, 0.5f, 1);	

	// enables the depth test state
	glEnable(GL_DEPTH_TEST);

	// main program loop
	// loops until the passed in window is set to close
	while (glfwWindowShouldClose(window) == GLFW_FALSE)
	{
		inputcheck(window);

		// calls the concrete derived class update() method
		update(1.0f);

		// calls the concrete derived class draw() method
		draw();

		// swaps the buffers of the passed in window
		glfwSwapBuffers(window);

		// checks for inputs sent by the OS
		glfwPollEvents();
	}

	// calls the concrete derived class shutdown() method
	shutdown();
}

