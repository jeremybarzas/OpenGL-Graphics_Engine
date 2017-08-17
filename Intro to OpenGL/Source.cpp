#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

int main()
{
	// intiialize glfw
	glfwInit();
	
	// create a new window to be rendered
	GLFWwindow* window = glfwCreateWindow(400, 400, "Computer Graphics", nullptr, nullptr);

	// make passed in window the current context
	glfwMakeContextCurrent(window);

	// function that remaps all of OpenGL’s function calls to the correct versions and feature sets.
	ogl_LoadFunctions();

	// sets the color the screen will clear to
	glClearColor(0, 0, 0, 1);

	// enables the depth buffer
	glEnable(GL_DEPTH_TEST);

	// loop while window is open
	while (glfwWindowShouldClose(window) == false)
	{
		// GL_COLOR_BUFFER_BIT informs OpenGL to wipe the back-buffer colours clean.
		// GL_DEPTH_BUFFER_BIT informs it to clear the distance to the closest pixels.
		// If we didn’t do this then OpenGL may think the image of the last frame is still there and our new visuals may not display.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// check for input of the escape key.
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			// sets that the window should be closed
			glfwSetWindowShouldClose(window, true);		

		// change color to red if r is pressed
		if (glfwGetKey(window, GLFW_KEY_R))
			glClearColor(1, 0, 0, 1);

		// change color to green if g is pressed
		if (glfwGetKey(window, GLFW_KEY_G))
			glClearColor(0, 1, 0, 1);

		// change color to blue if b is pressed
		if (glfwGetKey(window, GLFW_KEY_B))
			glClearColor(0, 0, 1, 1);		

		// updates the monitors display by swapping the rendered back buffer
		glfwSwapBuffers(window);

		// checks the events sent by the operating system for keybaord and mouse input
		glfwPollEvents();
	}

	// terminates glfw
	glfwTerminate();

	return 0;
}