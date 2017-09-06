#include "RenderGeometryApp.h"



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

	// sets the view and world transforms of the camera
	eye = glm::vec3(5, 5, 5);
	center = glm::vec3(0);
	up = glm::vec3(0, 1, 0);
	m_camera->setLookat(eye, center, up);
	m_camera->setPosition(glm::vec3(10, 10, 10));

	// sets the perspective view of the camera
	m_camera->setPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);	

	// Shader object pointer initialization
	m_shader = new Shader();

	// create and complie shaders passed by filename
	m_shader->load("$(SolutionDir)bin\Shaders\DefaultVertexShader.vert", GL_VERTEX_SHADER);
	m_shader->load("$(SolutionDir)bin\Shaders\DefaultFragmentShader.frag", GL_FRAGMENT_SHADER);	

	// attach shaders and link program
	m_shader->attach();

	// Mesh object startup function calls
	// create vertex and index arrays to pas to initialize
	Vertex a = { glm::vec4(-5,  0, 0, 1)		, glm::vec4(.1, .1, .1, 1) }; //bottom left	
	Vertex b = { glm::vec4(5,  0, 0, 1)			, glm::vec4(.1, .1, .1, 1) }; //bottom right
	Vertex c = { glm::vec4(5, -5, 0, 1)			, glm::vec4(.1, .1, .1, 1) }; //top left
	Vertex d = { glm::vec4(-5, -5, 0, 1)		, glm::vec4(1, 0, 0, 1) }; //top right
	Vertex e = { glm::vec4(-5,  5, 0, 1)		, glm::vec4(0, 0, 1, 1) }; //top right	

	std::vector<Vertex> vertices{ a,b,c,d,e };
	std::vector<unsigned int> indices{ 0, 1, 2, 0, 2, 3, 0, 4, 1 };

	// Mesh object pointer initialization
	m_mesh = new Mesh();

	// pass created arrays to assign mesh member variables 
	m_mesh->initialize(vertices, indices);

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
		//sun = glm::translate(glm::vec3(1, 0, 0)) * sun;
		// calculate the forward vector of the cameras current rotation		
		// apply movement along forward vector scaled by deltatime / multiplier
		m_camera->setPosition(-forward);
	}

	// camera strafe backward
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		// apply movement along forward vector scaled by deltatime / multiplier
		m_camera->setPosition(forward);
	}

	// camera strafe left
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_camera->setPosition(-right);
	}

	// camera strafe right
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_camera->setPosition(right);
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
	glUniformMatrix4fv(m_shader->getUniform("projectionViewWorldMatrix"), 1, false, glm::value_ptr(m_camera->m_projectionView));

	// bind vertex array object
	m_mesh->bind();

	// set to draw wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// draws each element
	glDrawElements(GL_TRIANGLES, m_mesh->m_index_count, GL_UNSIGNED_INT, 0);

	// unbind vertex array object
	m_mesh->unbind();

	//clear shader program
	m_shader->unbind();
}

void RenderGeometryApp::shutdown()
{	
}

