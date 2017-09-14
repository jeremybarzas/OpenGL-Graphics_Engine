#include "RenderGeometryApp.h"

#define PI 3.14f


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
	m_shader->defaultLoad();
	//m_shader->lightingLoad();
	//m_shader->load(".bin\Shaders\VertexShader.vert", GL_VERTEX_SHADER);
	//m_shader->load(".bin\Shaders\FragmentShader.frag", GL_FRAGMENT_SHADER);
	
	// attach shaders and link program
	m_shader->attach();

	/*========== Mesh Startup ==========*/
	// parameters = radius, points, meridians
	// generates verts and indices of sphere and pass them into m_mesh->initialize()
	genSphere(5.0f, 12, 16);

	// generate, bind, and buffer the vao, vbo, and ibo then cleanup
	m_mesh->create_buffers();	
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
		//std::cout << "delta mouse:: " << glm::to_string(glm::vec2(deltaX, deltaY)) << "\n";
	}
	m_camera->update(deltaTime);
}

void RenderGeometryApp::draw()
{
	// use shader program
	m_shader->bind();
	
	// create and assign uniform	
	glUniformMatrix4fv(m_shader->getUniform("projectionViewWorld"), 1, false, glm::value_ptr(m_camera->m_projectionView));
	
	// bind vertex array object
	m_mesh->bind();
	
	// set to draw wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
	for (int i = 0; i < numOfMeridians + 1; i++)
	{
		// calculate slice
		float slice = (PI * 2.0f) / numOfMeridians;

		// calculate phi
		float phi = i * slice;

		// loop per point
		for (int j = 0; j < points.size(); j++)
		{
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

void RenderGeometryApp::genSphere(float radius, unsigned int numOfPoints, unsigned int numOfMeridians)
{
	/*========== Generate Sphere Information ==========*/
	// generate verts for half of a circle
	std::vector<glm::vec4> halfCircleVerts = generateHalfCircle(radius, numOfPoints);

	// rotate half circle around to generate entire sphere verts
	std::vector<glm::vec4> wholeSphereVerts = rotatePoints(halfCircleVerts, numOfMeridians);

	// generate indices
	std::vector<unsigned int> sphereIndices = genIndices(numOfMeridians, numOfPoints);
	
	// convert wholeSphereVerts into a std::vector<Vertex>
	std::vector<Vertex> sphereVerts;
	for (int i = 0; i < wholeSphereVerts.size(); i++)
	{
		Vertex newVert = Vertex {wholeSphereVerts[i], glm::vec4(.75, 0, .75, 1)};
		sphereVerts.push_back(newVert);	
	}
	
	/*========== Initialize Mesh with Sphere Information ==========*/
	// pass verts and indices into mesh->initalize() function
	m_mesh->initialize(sphereVerts, sphereIndices);

	// break point 
	return;
}
