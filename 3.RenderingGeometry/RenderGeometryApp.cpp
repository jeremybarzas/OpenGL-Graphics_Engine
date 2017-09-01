#include "RenderGeometryApp.h"



RenderGeometryApp::RenderGeometryApp()
{	
}


RenderGeometryApp::~RenderGeometryApp()
{
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

	// ========== Create Shaders ==========
	const char* vsSource = "#version 410\n \
							layout(location=0) in vec4 position; \
							layout(location=1) in vec4 colour; \
							out vec4 vColour; \
							uniform mat4 projectionViewWorldMatrix; \
							void main() { vColour = colour; gl_Position = projectionViewWorldMatrix * position; }";

	const char * fsSource = "#version 410\n \
							in vec4 vColour; \
							out vec4 fragColor; \
							void main() { fragColor = vColour; }";

	// ========== Complie Shaders ==========
	int success = GL_FALSE;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char **)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char **)&fsSource, 0);
	glCompileShader(fragmentShader);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	
	//generateGrid(10, 10);	

	// mesh object initialization
	m_mesh = new Mesh();

	// Mesh object start up functionality	
	m_mesh->startup_portion();	
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
	glUseProgram(m_programID);
	unsigned int projectionViewUniform = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(m_camera->m_projectionView));

	m_mesh->draw_portion();

	//// bind the Vertex Array Object
	//glBindVertexArray(m_VAO);	

	//// makes flat plane into a wireframe grid
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//unsigned int indexCount = (m_rows - 1) * (m_cols - 1) * 6;
	//glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);	

	//// clears the Vertex Array Object bind
	//glBindVertexArray(0);

	glUseProgram(0);
}

void RenderGeometryApp::shutdown()
{	
}

void RenderGeometryApp::generateGrid(unsigned int rows, unsigned int cols)
{
	// sets the variables that control the girds length and width
	m_rows = rows;
	m_cols = cols;

	// fill array of verts for a grid
	Vertex* vertArray = new Vertex[m_rows * m_cols];
	for (unsigned int r = 0; r < m_rows; ++r)
	{
		for (unsigned int c = 0; c < m_cols; ++c)
		{
			vertArray[r * m_cols + c].position = glm::vec4((float)c, 0, (float)r, 1);

			glm::vec3 color = glm::vec3(sinf((c / (float)(m_cols - 1)) * (r / (float)(m_rows - 1))));
			vertArray[r * m_cols + c].color = glm::vec4(color, 1);
		}
	}

	// fill array with indices of the verts of the 2 triangles
	// defining index count based off quad count (2 triangles per quad)
	unsigned int* auiIndices = new unsigned int[(m_rows - 1) * (m_cols - 1) * 6];
	unsigned int index = 0;
	for (unsigned int r = 0; r < (m_rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (m_cols - 1); ++c)
		{
			// triangle 1
			auiIndices[index++] = r * m_cols + c;
			auiIndices[index++] = (r + 1) * m_cols + c;
			auiIndices[index++] = (r + 1) * m_cols + (c + 1);

			// triangle 2
			auiIndices[index++] = r * m_cols + c;
			auiIndices[index++] = (r + 1) * m_cols + (c + 1);
			auiIndices[index++] = r * m_cols + (c + 1);		
		}	
	}

	// ========== Generate Buffer Objects ==========

	// generate Vertex Array Object
	glGenVertexArrays(1, &m_VAO);

	// generate Vertex Buffer Object
	glGenBuffers(1, &m_VBO);

	// generate Index Buffer Object
	glGenBuffers(1, &m_IBO);	

	// ========== Bind Buffer Objects ==========
	// bind Vertex Array Object
	glBindVertexArray(m_VAO);

	// bind Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);	

	// buffer the Vertex Buffer Object's data
	glBufferData(GL_ARRAY_BUFFER, (m_rows* m_cols) * sizeof(Vertex), vertArray, GL_STATIC_DRAW);	

	// enable vertex attribute array indices 0 and 1
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	// assign vertex attribute array indices 0 and 1
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4)));

	// bind Index Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	
	// buffer the Index Buffer Object's data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (m_rows - 1) * (m_cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);	

	// ========== Cleanup Buffer Objects ==========
	// clear the Vertex Array Object bind
	glBindVertexArray(0);

	// clear the Vertex Buffer Object bind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// clear the Index Buffer Object bind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	

	// ========== Delete arrays ==========
	delete[] vertArray;
	delete[] auiIndices;
}

