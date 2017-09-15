#include "RenderGeometryApp.h"
#include <iostream>
#include "imgui.h"
#include <imgui_impl_glfw_gl3.h>
#define PI 3.14159265359


RenderGeometryApp::RenderGeometryApp()
{
}

RenderGeometryApp::~RenderGeometryApp()
{
	delete m_camera;
	delete m_mesh;
	delete m_shader;
}

void RenderGeometryApp::startup()
{
	// camera object initialization
	m_camera = new Camera();

	// Mesh object pointer initialization
	m_mesh = new Mesh();

	// Shader object pointer initialization
	m_shader = new Shader();

	/*========== Camera Startup ==========*/
	// sets the view and world transforms of the camera
	eye = glm::vec3(5, 5, 5);
	center = glm::vec3(0);
	up = glm::vec3(0, 1, 0);
	m_camera->setLookat(eye, center, up);
	m_camera->setPosition(glm::vec3(10, 10, 10));

	// sets the perspective view of the camera
	m_camera->setPerspective(PI * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	/*========== Shader Startup ==========*/
	// create and complie shaders passed by filename	
	m_shader->load("./Shaders/Phong.vert", GL_VERTEX_SHADER);
	m_shader->load("./Shaders/Phong.frag", GL_FRAGMENT_SHADER);
	//m_shader->defaultLoad();
	
	// attach shaders and link program
	m_shader->attach();

	/*========== Mesh Startup ==========*/

	/*========== Generate Sphere Information ==========*/	
	float radius;
	unsigned np, nm;
	radius = 5.f;
	np = 12;
	nm = 16;	

	// generate vertex info for a half circle
	std::vector<glm::vec4> halfCircleVerts = generateHalfCircle(radius, np);

	// rotate half circle around to generate entire sphere verts
	std::vector<glm::vec4> spherePoints = rotatePoints(halfCircleVerts, nm);

	// generate indices for triangle strip
	std::vector<unsigned int> sphereIndices = genIndices(nm, np);	

	// convert spherePoints into a std::vector<Vertex>
	std::vector<Vertex> verts;
	for (auto p : spherePoints)
	{
		Vertex vert = { p, glm::vec4(.75, 0, .75, 1), glm::normalize(p) };
		verts.push_back(vert);
	}

	// initialize with sphere vertex and index information
	m_mesh->initialize(verts, sphereIndices);

	/*========== Generate Plane Information ==========*/
	//std::vector<glm::vec4> planePoints;
	//std::vector<unsigned int> planeIndices;
	//unsigned int width, length;
	//width = 5;
	//length = 5;

	//// near left
	//planePoints.push_back(glm::vec4(0, 0, 0, 1));

	//// near right
	//planePoints.push_back(glm::vec4(width, 0, 0, 1));

	//// far left
	//planePoints.push_back(glm::vec4(0, 0, length, 1));

	//// far right
	//planePoints.push_back(glm::vec4(width, 0, length, 1));

	//std::vector<Vertex> planeVerts;
	//for (auto p : planePoints)
	//{
	//	Vertex vert = { p, glm::vec4(.75, 0, .75, 1), glm::normalize(p) };
	//	planeVerts.push_back(vert);
	//}

	//planeIndices.push_back(0);
	//planeIndices.push_back(1);
	//planeIndices.push_back(2);
	//planeIndices.push_back(3);
	//planeIndices.push_back(0xFFFF);
	//
	//// initialize with plane vertex and index information
	//m_mesh->initialize(planeVerts, planeIndices);

	/*========== Generate Cube Information ==========*/
	//std::vector<glm::vec4> cubePoints;
	//std::vector<unsigned int> cubeIndices;
	//unsigned int width, length, size;
	//width = 5;
	//length = 5;
	//size = 5;

	///*===== Bottom Points =====*/
	//// near left
	//cubePoints.push_back(glm::vec4(0, 0, 0, 1));

	//// near right
	//cubePoints.push_back(glm::vec4(width, 0, 0, 1));

	//// far left
	//cubePoints.push_back(glm::vec4(0, 0, length, 1));

	//// far right
	//cubePoints.push_back(glm::vec4(width, 0, length, 1));

	///*===== Top Points =====*/
	//// near left
	//cubePoints.push_back(glm::vec4(0, size, 0, 1));

	//// near right
	//cubePoints.push_back(glm::vec4(width, size, 0, 1));

	//// far left
	//cubePoints.push_back(glm::vec4(0, size, length, 1));

	//// far right
	//cubePoints.push_back(glm::vec4(width, size, length, 1));

	//std::vector<Vertex> cubeVerts;
	//for (auto p : cubePoints)
	//{
	//	Vertex vert = { p, glm::vec4(.75, 0, .75, 1), glm::normalize(p) };
	//	cubeVerts.push_back(vert);
	//}

	//// bottom face
	//cubeIndices.push_back(0);
	//cubeIndices.push_back(1);
	//cubeIndices.push_back(2);
	//cubeIndices.push_back(3);
	//cubeIndices.push_back(0xFFFF);

	//// top face
	//cubeIndices.push_back(4);
	//cubeIndices.push_back(5);
	//cubeIndices.push_back(6);
	//cubeIndices.push_back(7);
	//cubeIndices.push_back(0xFFFF);

	//// front face
	//cubeIndices.push_back(0);
	//cubeIndices.push_back(1);
	//cubeIndices.push_back(4);
	//cubeIndices.push_back(5);
	//cubeIndices.push_back(0xFFFF);

	//// back face
	//cubeIndices.push_back(2);
	//cubeIndices.push_back(3);
	//cubeIndices.push_back(6);
	//cubeIndices.push_back(7);
	//cubeIndices.push_back(0xFFFF);

	//// right face
	//cubeIndices.push_back(1);
	//cubeIndices.push_back(3);
	//cubeIndices.push_back(5);
	//cubeIndices.push_back(7);
	//cubeIndices.push_back(0xFFFF);

	//// left face
	//cubeIndices.push_back(0);
	//cubeIndices.push_back(2);
	//cubeIndices.push_back(4);
	//cubeIndices.push_back(6);
	//cubeIndices.push_back(0xFFFF);

	//// initialize with plane vertex and index information
	//m_mesh->initialize(cubeVerts, cubeIndices);
}

void RenderGeometryApp::update(float deltaTime)
{
	// camera strafe forward
	glm::vec4 forward = m_camera->m_transform->getWorld()[2];
	glm::vec4 right = m_camera->m_transform->getWorld()[0];
	glm::vec4 up = m_camera->m_transform->getWorld()[1];

	if (glfwGetKey(m_window, 'W') == GLFW_PRESS)
	{
		m_camera->setPosition(-forward * .33);
	}

	// camera strafe backward
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		// apply movement along forward vector scaled by deltatime / multiplier
		m_camera->setPosition(forward * .33);
	}

	// camera strafe left
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_camera->setPosition(-right * .33);
	}

	// camera strafe right
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_camera->setPosition(right * .33);
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
		
		//m_camera->m_transform->rotate(deltaX, YAXIS);
	}

	m_camera->update(deltaTime);
}

void RenderGeometryApp::draw()
{	
	// start imgui
	ImGui::Begin("hello");	

	// end imgui
	ImGui::End();

	// use shader program
	m_shader->bind();

	// create and assign uniform	
	glUniformMatrix4fv(m_shader->getUniform("projectionViewWorld"), 1, false, glm::value_ptr(m_camera->m_projectionView));

	// bind vertex array object
	m_mesh->bind();

	// set to draw wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// enable primitive restart
	glEnable(GL_PRIMITIVE_RESTART);

	// assign what the restart index is
	glPrimitiveRestartIndex(0xFFFF);

	// draws the buffered data of the currently bound VAO
	glDrawElements(GL_TRIANGLE_STRIP, m_mesh->m_index_count, GL_UNSIGNED_INT, 0);

	// disable the primitive restart 
	glDisable(GL_PRIMITIVE_RESTART);

	// unbind vertex array object
	m_mesh->unbind();

	//clear shader program
	m_shader->unbind();

	// set polygon mode for imgui
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RenderGeometryApp::shutdown()
{
}

std::vector<glm::vec4> RenderGeometryApp::generateHalfCircle(float radius, unsigned int points)
{
	// will be used the store the points of a half circle
	std::vector<glm::vec4> halfCircle = std::vector<glm::vec4>(points);

	// loop per point to generate each slice
	for (int i = 0; i < points; i++)
	{
		// calculate slice
		float slice = PI / (points - 1);

		// calculate theta
		float theta = i * slice;

		// x = cos(theta) and y = sin(theta) would give you a horizontal half circle.
		// but since we are generating triangle strips and need to be rotating this half circle differently,
		// you would reverse it to orient the half circle vertically.
		// to be correctly oriented with how we want to draw the triangle strips.		
		halfCircle[i].x = sin(theta) * radius;
		halfCircle[i].y = cos(theta) * radius;
		halfCircle[i].z = 0.0f;
		halfCircle[i].w = 1.0f;
	}
	//return the array of the points that make up the half circle
	return halfCircle;
}

std::vector<glm::vec4> RenderGeometryApp::rotatePoints(std::vector<glm::vec4> points, unsigned int numOfMeridians)
{
	// will be used to store enitre sphere to be returned
	std::vector<glm::vec4> wholeSphere;

	// loop per meridian
	for (int i = 0; i <= numOfMeridians; i++)
	{		
		// calculate slice
		float slice = (PI * 2.0f) / numOfMeridians;

		// calculate phi
		float phi = i * slice;

		// loop per point
		for (int j = 0; j < points.size(); j++)
		{
			glm::cos(25);
			// calculate each new value of the new vec4
			float newX = points[j].x * cos(phi) + points[j].z * sin(phi);
			float newY = points[j].y;
			float newZ = points[j].z * cos(phi) - points[j].x * sin(phi);;
			float newW = points[j].w = 1.0f;

			// push new vec4 onto list of points that make up entire sphere
			wholeSphere.push_back(glm::vec4(newX, newY, newZ, newW));
		}
	}
	// return the array of points that make up the entire sphere
	return wholeSphere;
}

std::vector<unsigned int> RenderGeometryApp::genIndices(unsigned int nm, unsigned int np)
{
	// create array of unsigned ints to store the index information
	std::vector<unsigned int> indices;

	unsigned int start;
	unsigned int botLeft;
	unsigned int botRight;

	for (int i = 0; i < nm; i++)
	{
		start = i * np;

		for (int j = 0; j < np; j++)
		{
			botLeft = start + j;
			botRight = botLeft + np;
			indices.push_back(botLeft);
			indices.push_back(botRight);
		}
		indices.push_back(0xFFFF);
	}

	// return array of indices in order to be drawn
	return indices;
}

