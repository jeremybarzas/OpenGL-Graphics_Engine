#include "Application.h"
#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include "Gizmos.h"

Application::Application() : m_window(nullptr)
{
}

Application::~Application()
{
}

void Application::run(const char * title, unsigned int width, unsigned int height, bool fullscreen)
{
	this->startup();

	if (glfwInit() == GL_FALSE)
		return;

	GLFWmonitor* monitor = (fullscreen) ? glfwGetPrimaryMonitor() : nullptr;
	
	m_window = glfwCreateWindow(width, height, title, monitor, nullptr);

	glfwMakeContextCurrent(m_window);
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return;
	}

	glClearColor(0.5f, 0, 0.5f, 1);

	glEnable(GL_DEPTH_TEST);

	double prevTime = glfwGetTime();
	double currTime = 0;
	double deltaTime = 0;	

	while (!m_gameover)
	{
		currTime = glfwGetTime();
		deltaTime - currTime - prevTime;
		prevTime = currTime;
		glfwPollEvents();
		update(deltaTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw();
		glfwSwapBuffers(m_window);
		m_gameover = (glfwWindowShouldClose(m_window) == GLFW_TRUE);
	}
}
