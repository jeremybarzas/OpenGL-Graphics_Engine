#include "Application.h"
#include "Gizmos.h"


Application::Application()
{	
}


Application::~Application()
{
}

void inputcheck(GLFWwindow* window)
{
	
}

void Application::run(float width, float height, const char * title, bool fullscreen)
{
	// initializes glfw
	glfwInit();

	// sets control time
	prevTime = glfwGetTime();

	// calls the concrete derived class startup() method
	startup();	

	// creates a window to draw in with OpenGL
	fullscreen == false ? monitor = nullptr : monitor = glfwGetPrimaryMonitor();
	window = glfwCreateWindow(width, height, title, monitor, nullptr);

	// makes the pased in window the current context
	glfwMakeContextCurrent(window);

	// loads all of the OpenGL extenstions
	ogl_LoadFunctions();

	// initilizes the Gizmos
	Gizmos::create();

	// set window clear color to grey
	glClearColor(0.5f, 0.5f, 0.5f, 1);	

	// enables the depth test state
	glEnable(GL_DEPTH_TEST);

	// main program loop
	// loops until the passed in window is set to close
	while (glfwWindowShouldClose(window) == GLFW_FALSE)
	{		
		// sets the loop condition to true if "escape" is pressed
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, GL_TRUE);

		// clears both the color and depth buffer so the window doesn't fail to update visuals
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// calculates delta time
		float currTime = glfwGetTime();
		float deltaTime = currTime - prevTime;
		
		// calls the concrete derived class update() method
		update(deltaTime);

		// calls the concrete derived class draw() method
		draw();

		// swaps the buffers of the passed in window
		glfwSwapBuffers(window);

		// checks for inputs sent by the OS
		glfwPollEvents();
	}

	// terminates glfw
	glfwTerminate();

	// calls the concrete derived class shutdown() method
	shutdown();
}

