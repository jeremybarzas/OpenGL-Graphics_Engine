#include "gl_core_4_4.h"
#include "Gizmos.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <GLFW\glfw3.h>

#include "IntroductionApp.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

int main()
{
	Application* app = new IntroductionApp();	

	// run is invoked from application
	// run will call startup from introductionapp
	// run will call update from introductionapp
	// run will call draw from introductionapp
	app->run("Intro to OpenGL", 1600, 900, false);	
	
	delete app;
	
	/*=====================================================================*/

	//// intiialize glfw
	//glfwInit();
	//
	//// create a new window to be rendered
	//GLFWwindow* window = glfwCreateWindow(1200, 800, "Computer Graphics", nullptr, nullptr);

	//// make passed in window the current context
	//glfwMakeContextCurrent(window);

	//// function that remaps all of OpenGL’s function calls to the correct versions and feature sets.
	//ogl_LoadFunctions();

	//// sets the color the screen will clear to
	//glClearColor(.5, .5, .5, 1);

	//// initilizes the Gizmos
	////Gizmos::create();

	////sets up virtual camera
	////mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	////mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	//// enables the depth buffer
	//glEnable(GL_DEPTH_TEST);

	//// loop while window is open
	//while (glfwWindowShouldClose(window) == false)
	//{
	//	// GL_COLOR_BUFFER_BIT informs OpenGL to wipe the back-buffer colours clean.
	//	// GL_DEPTH_BUFFER_BIT informs it to clear the distance to the closest pixels.
	//	// If we didn’t do this then OpenGL may think the image of the last frame is still there and our new visuals may not display.
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	/*
	//	// removes all shapes and lines
	//	Gizmos::clear();

	//	// creates transform handles
	//	Gizmos::addTransform(glm::mat4(1));

	//	// colors to be used
	//	vec4 white(1);
	//	vec4 black(0, 0, 0, 1);

	//	// generates a grid of lines
	//	for (int i = 0; i < 21; ++i) 
	//	{ 
	//		Gizmos::addLine(vec3(-10 + i, 0, 10),
	//						vec3(-10 + i, 0, -10),
	//						i == 10 ? white : black);

	//		Gizmos::addLine(vec3(10, 0, -10 + i),
	//						vec3(-10, 0, -10 + i),
	//						i == 10 ? white : black);
	//	}	
	//	
	//	// draws the current gizmo buffers
	//	Gizmos::draw(projection * view);
	//	*/

	//	// check for input of the escape key.
	//	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	//		// sets that the window should be closed
	//		glfwSetWindowShouldClose(window, true);		

	//	// change color to red if r is pressed
	//	if (glfwGetKey(window, GLFW_KEY_R))
	//		glClearColor(1, 0, 0, 1);

	//	// change color to green if g is pressed
	//	if (glfwGetKey(window, GLFW_KEY_G))
	//		glClearColor(0, 1, 0, 1);

	//	// change color to blue if b is pressed
	//	if (glfwGetKey(window, GLFW_KEY_B))
	//		glClearColor(0, 0, 1, 1);		

	//	// updates the monitors display by swapping the rendered back buffer
	//	glfwSwapBuffers(window);

	//	// checks the events sent by the operating system for keybaord and mouse input
	//	glfwPollEvents();
	//}

	// destroys all Gizmos
	//Gizmos::destroy();

	// terminates glfw
	//glfwTerminate();

	// default return of the main application
	return 0;
}
