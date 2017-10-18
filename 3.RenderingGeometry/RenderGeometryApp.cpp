#define GLM_FORCE_SWIZZLE
#include "RenderGeometryApp.h"

#include <iostream>
#include "imgui.h"
#include <imgui_impl_glfw_gl3.h>
#define PI 3.14159265359

// texture
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master\stb_image.h"

// global sphere variables
float radius = 5;
int numP = 100;
int numM = 100;

auto option1 = GL_LINE;

RenderGeometryApp::RenderGeometryApp()
{
	// camera object initialization
	m_camera = new Camera();

	// Mesh object pointer initialization
	m_mesh = new Mesh();

	// Shader object pointer initialization
	m_shader = new Shader();

	// Light object 
	m_light = Light();
}

RenderGeometryApp::~RenderGeometryApp()
{
	delete m_camera;
	delete m_mesh;
	delete m_shader;
}

void RenderGeometryApp::startup()
{
	/*========== Camera Startup ==========*/
	// sets the view and world transforms of the camera
	eye = glm::vec3(50, 15, 50);
	center = glm::vec3(0);
	up = glm::vec3(0, 1, 0);
	m_camera->setLookAt(eye, center, up);


	// sets the perspective view of the camera
	m_camera->setPerspective(PI * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	/*========== Shader Startup ==========*/
	// create and complie shaders passed by filename	
	//m_shader->defaultLoad();

	/*========== Vertex Shader Load ==========*/
	//m_shader->load("./Shaders/DefaultVertex.vert", GL_VERTEX_SHADER);
	//m_shader->load("./Shaders/PerlinVert.vert", GL_VERTEX_SHADER);

	/*========== Fragment Shader Load ==========*/
	//m_shader->load("./Shaders/DefaultFragment.frag", GL_FRAGMENT_SHADER);
	//m_shader->load("./Shaders/HemisphereLighting.frag", GL_FRAGMENT_SHADER);
	//m_shader->load("./Shaders/DiffuseLighting.frag", GL_FRAGMENT_SHADER);
	//m_shader->load("./Shaders/SpecularLighting.frag", GL_FRAGMENT_SHADER);
	//m_shader->load("./Shaders/Phong.frag", GL_FRAGMENT_SHADER);
	//m_shader->load("./Shaders/BlinnPhong.frag", GL_FRAGMENT_SHADER);
	//m_shader->load("./Shaders/CustomFragment.frag", GL_FRAGMENT_SHADER);	
	//m_shader->load("./Shaders/TexturedLighting.frag", GL_FRAGMENT_SHADER);
	//m_shader->load("./Shaders/PerlinFrag.frag", GL_FRAGMENT_SHADER);

	/*========== Attach Loaded Shader ==========*/
	// attach shaders and link program
	//m_shader->attach();

	//genPlane(32, 32, 32, 0);
}

void RenderGeometryApp::update(float deltaTime)
{
	m_camera->update(deltaTime);
}

void RenderGeometryApp::draw()
{
	// Lighting Options
	ImGui::Begin("Lighting Options");

	ImGui::SliderFloat("Light Direction X", &m_light.lightDirX, -1, 1);
	ImGui::SliderFloat("Light Direction Y", &m_light.lightDirY, -1, 1);
	ImGui::SliderFloat("Light Direction Z", &m_light.lightDirZ, -1, 1);
	ImGui::SliderFloat("Ambient Strength", &m_light.ambientStrength, 0, 1);
	ImGui::SliderFloat("Diffuse Strength", &m_light.diffuseStrength, 0, 1);
	ImGui::SliderFloat("Specular Strength", &m_light.specularStrength, 0, 1);
	ImGui::SliderFloat("Specular Power", &m_light.specularPower, 1, 200);

	ImGui::End();
	
	// Geometry Options
	ImGui::Begin("Geometry Options");	

	if (ImGui::Button("Plane Mesh"))
	{
		glDeleteBuffers(1, &m_mesh->m_vbo);
		glDeleteBuffers(1, &m_mesh->m_ibo);
		glDeleteVertexArrays(1, &m_mesh->m_vao);

		delete m_mesh;
		m_mesh = new Mesh();

		delete m_shader;
		m_shader = new Shader();

		m_shader->load("./Shaders/DefaultVertex.vert", GL_VERTEX_SHADER);
		m_shader->load("./Shaders/DefaultFragment.frag", GL_FRAGMENT_SHADER);
		m_shader->attach();

		int width = 32;
		int length = 32;
		int dims = 32;
		genPlane(width, length, dims);
	}

	if (ImGui::Button("Plane Texture"))
	{
		glDeleteBuffers(1, &m_mesh->m_vbo);
		glDeleteBuffers(1, &m_mesh->m_ibo);
		glDeleteVertexArrays(1, &m_mesh->m_vao);

		delete m_mesh;
		m_mesh = new Mesh();

		delete m_shader;
		m_shader = new Shader();

		delete m_shader;
		m_shader = new Shader();

		m_shader->load("./Shaders/DefaultVertex.vert", GL_VERTEX_SHADER);
		m_shader->load("./Shaders/TexturedLighting.frag", GL_FRAGMENT_SHADER);
		m_shader->attach();

		int width = 32;
		int length = 32;
		int dims = 32;

		int imageWidth = 0, imageHeight = 0, imageFormat = 0;
		unsigned char* data = stbi_load("./Textures/crate.png", &imageWidth, &imageHeight, &imageFormat, STBI_default);
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		stbi_image_free(data);

		genPlane(width, length, dims);
	}

	if (ImGui::Button("Plane Perlin"))
	{
		glDeleteBuffers(1, &m_mesh->m_vbo);
		glDeleteBuffers(1, &m_mesh->m_ibo);
		glDeleteVertexArrays(1, &m_mesh->m_vao);

		delete m_mesh;
		m_mesh = new Mesh();

		delete m_shader;
		m_shader = new Shader();

		delete m_shader;
		m_shader = new Shader();

		m_shader->load("./Shaders/PerlinVert.vert", GL_VERTEX_SHADER);
		m_shader->load("./Shaders/PerlinFrag.frag", GL_FRAGMENT_SHADER);
		m_shader->attach();

		int width = 32;
		int length = 32;
		int dims = 32;

		float* perlinData = perlinNoise(dims);
		glGenTextures(1, &m_perlinTexture);
		glBindTexture(GL_TEXTURE_2D, m_perlinTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, length, 0, GL_RGB, GL_UNSIGNED_BYTE, perlinData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		stbi_image_free(perlinData);

		genPlane(width, length, dims);
	}

	if (ImGui::Button("Sphere Mesh"))
	{
		glDeleteBuffers(1, &m_mesh->m_vbo);
		glDeleteBuffers(1, &m_mesh->m_ibo);
		glDeleteVertexArrays(1, &m_mesh->m_vao);

		delete m_mesh;
		m_mesh = new Mesh();

		delete m_shader;
		m_shader = new Shader();

		m_shader->load("./Shaders/DefaultVertex.vert", GL_VERTEX_SHADER);
		m_shader->load("./Shaders/DefaultFragment.frag", GL_FRAGMENT_SHADER);
		m_shader->attach();

		radius = 10;
		numP = 32;
		numM = 32;
		genSphere(radius, numP, numM);
	}	

	if (ImGui::Button("Sphere Texture"))
	{
		glDeleteBuffers(1, &m_mesh->m_vbo);
		glDeleteBuffers(1, &m_mesh->m_ibo);
		glDeleteVertexArrays(1, &m_mesh->m_vao);

		delete m_mesh;
		m_mesh = new Mesh();

		delete m_shader;
		m_shader = new Shader();

		m_shader->load("./Shaders/DefaultVertex.vert", GL_VERTEX_SHADER);
		m_shader->load("./Shaders/TexturedLighting.frag", GL_FRAGMENT_SHADER);
		m_shader->attach();

		radius = 10;
		numP = 32;
		numM = 32;

		int imageWidth = 0, imageHeight = 0, imageFormat = 0;
		unsigned char* data = stbi_load("./Textures/earth.jpg", &imageWidth, &imageHeight, &imageFormat, STBI_default);
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		stbi_image_free(data);

		genSphere(radius, numP, numM);
	}

	if (ImGui::Button("Cube Mesh"))
	{
		glDeleteBuffers(1, &m_mesh->m_vbo);
		glDeleteBuffers(1, &m_mesh->m_ibo);
		glDeleteVertexArrays(1, &m_mesh->m_vao);

		delete m_mesh;
		m_mesh = new Mesh();

		delete m_shader;
		m_shader = new Shader();

		m_shader->load("./Shaders/DefaultVertex.vert", GL_VERTEX_SHADER);
		m_shader->load("./Shaders/DefaultFragment.frag", GL_FRAGMENT_SHADER);
		m_shader->attach();

		genCube(10,10,10);
	}

	ImGui::End();	

	// Mesh Options
	ImGui::Begin("Mesh Options");		

	if (ImGui::Button("Line"))
	{
		// set to draw wireframe
		option1 = GL_LINE;		
	}

	if (ImGui::Button("Fill"))
	{
		// set to draw faces
		option1 = GL_FILL;
	}

	ImGui::End();

	// use shader program
	m_shader->bind();

	// create and assign uniform
	glUniformMatrix4fv(m_shader->getUniform("projectionViewWorld"), 1, false, glm::value_ptr(m_camera->projectionView));

	glm::vec4 camPos = glm::vec4(m_camera->transform.World[3].xyz(), 1);

	glUniform1f(m_shader->getUniform("lightDirX"), m_light.lightDirX);
	glUniform1f(m_shader->getUniform("lightDirY"), m_light.lightDirY);
	glUniform1f(m_shader->getUniform("lightDirZ"), m_light.lightDirZ);
	glUniform1f(m_shader->getUniform("ambientStrength"), m_light.ambientStrength);
	glUniform1f(m_shader->getUniform("diffuseStrength"), m_light.diffuseStrength);
	glUniform1f(m_shader->getUniform("specularStrength"), m_light.specularStrength);
	glUniform1f(m_shader->getUniform("specularPower"), m_light.specularPower);
	glUniform4fv(m_shader->getUniform("cameraPosition"), 1, glm::value_ptr(camPos));

	// bind vertex array object
	m_mesh->bind();

	// set to draw wireframe
	glPolygonMode(GL_FRONT_AND_BACK, option1);

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

/*==================== Generate Geometry using Triangle Strips ====================*/
void RenderGeometryApp::genSphere(float radius, int np, int nm)
{
	std::vector<glm::vec4> meshPoints;
	std::vector<unsigned int> meshIndices;
	std::vector<Vertex> meshVerts;

	// generate vertex info for a half circle
	meshPoints = generateHalfCircle(radius, np);

	// rotate half circle around to generate entire sphere verts
	meshPoints = rotatePoints(meshPoints, nm);

	// generate indices for triangle strip
	meshIndices = genIndicesTriStrip(nm, np);

	// convert spherePoints into a std::vector<Vertex>	
	for (auto p : meshPoints)
	{
		Vertex vert = { p, glm::vec4(1), glm::normalize(p) };
		meshVerts.push_back(vert);
	}

	// setup UVs loop 
	int vertIndex = 0;
	for (unsigned int i = 0; i <= nm; i++)
	{
		for (unsigned int j = 0; j < np; j++)
		{
			meshVerts[vertIndex].uv = glm::vec2(i / ((float)np), j / ((float)nm - 1));
			vertIndex++;
			if (vertIndex == meshVerts.size())
			{
				break;
			}
		}
	}

	// initialize with plane vertex and index information
	m_mesh->initialize(meshVerts, meshIndices);

	// create and setup buffers
	m_mesh->create_buffers();
}

void RenderGeometryApp::genPlane(int width, int length, int dims)
{
	std::vector<glm::vec4> meshPoints;
	std::vector<unsigned int> meshIndices;
	std::vector<Vertex> meshVerts;

	// populate points
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			meshPoints.push_back(glm::vec4(i, 0, j, 1));
		}
	}

	// convert points to verts
	for (auto p : meshPoints)
	{
		Vertex vert = { p, glm::vec4(1,1,1,1), glm::normalize(p) };
		meshVerts.push_back(vert);
	}

	// assign UVs
	int vertIndex = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			meshVerts[vertIndex].uv = glm::vec2(i / ((float)width - 1), j / ((float)length - 1));
			vertIndex++;
		}
	}

	// assign vert indices
	unsigned int start;
	unsigned int botLeft;
	unsigned int botRight;

	for (int i = 0; i < width - 1; i++)
	{
		start = i * length;

		for (int j = 0; j < length; j++)
		{
			botLeft = start + j;
			botRight = botLeft + length;
			meshIndices.push_back(botLeft);
			meshIndices.push_back(botRight);
		}
		meshIndices.push_back(0xFFFF);
	}

	// initialize with plane vertex and index information
	m_mesh->initialize(meshVerts, meshIndices);

	// create and setup buffers
	m_mesh->create_buffers();
}

void RenderGeometryApp::genCube(int width, int length, int dims)
{
	std::vector<glm::vec4> meshPoints;
	std::vector<unsigned int> meshIndices;
	std::vector<Vertex> meshVerts;

	/*===== Bottom Points =====*/

	// near left
	meshPoints.push_back(glm::vec4(0, 0, 0, 1));

	// near right
	meshPoints.push_back(glm::vec4(width, 0, 0, 1));

	// far left
	meshPoints.push_back(glm::vec4(0, 0, length, 1));

	// far right
	meshPoints.push_back(glm::vec4(width, 0, length, 1));

	/*===== Top Points =====*/

	// near left
	meshPoints.push_back(glm::vec4(0, dims, 0, 1));

	// near right
	meshPoints.push_back(glm::vec4(width, dims, 0, 1));

	// far left
	meshPoints.push_back(glm::vec4(0, dims, length, 1));

	// far right
	meshPoints.push_back(glm::vec4(width, dims, length, 1));

	// turn points into vertices
	for (auto p : meshPoints)
	{
		Vertex vert = { p, glm::vec4(1), glm::normalize(p) };
		meshVerts.push_back(vert);
	}

	// bottom face
	meshIndices.push_back(0);
	meshIndices.push_back(1);
	meshIndices.push_back(2);
	meshIndices.push_back(3);
	meshIndices.push_back(0xFFFF);

	// top face
	meshIndices.push_back(4);
	meshIndices.push_back(5);
	meshIndices.push_back(6);
	meshIndices.push_back(7);
	meshIndices.push_back(0xFFFF);

	// front face
	meshIndices.push_back(0);
	meshIndices.push_back(1);
	meshIndices.push_back(4);
	meshIndices.push_back(5);
	meshIndices.push_back(0xFFFF);

	// back face
	meshIndices.push_back(2);
	meshIndices.push_back(3);
	meshIndices.push_back(6);
	meshIndices.push_back(7);
	meshIndices.push_back(0xFFFF);

	// right face
	meshIndices.push_back(1);
	meshIndices.push_back(3);
	meshIndices.push_back(5);
	meshIndices.push_back(7);
	meshIndices.push_back(0xFFFF);

	// left face
	meshIndices.push_back(0);
	meshIndices.push_back(2);
	meshIndices.push_back(4);
	meshIndices.push_back(6);
	meshIndices.push_back(0xFFFF);

	// initialize with plane vertex and index information
	m_mesh->initialize(meshVerts, meshIndices);

	// create and setup buffers
	m_mesh->create_buffers();
}

/*==================== Generate Sphere Vertex Data ====================*/
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

std::vector<unsigned int> RenderGeometryApp::genIndicesTriStrip(unsigned int nm, unsigned int np)
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

/*==================== Generate Perlin Noise ====================*/
float* RenderGeometryApp::perlinNoise(int dims)
{
	float* perlinData = new float[dims * dims];
	float scale = (1.0f / dims) * 3;
	int octaves = 6;

	for (int x = 0; x < dims; ++x)
	{
		for (int y = 0; y < dims; ++y)
		{
			float amplitude = 1.f;
			float persistence = 0.3f;
			perlinData[y * dims + x] = 0;

			perlinData[y* dims + x] = glm::perlin(glm::vec2(x, y) * scale) * 0.5f + 0.5f;
			for (int o = 0; o < octaves; ++o)
			{
				float freq = powf(2, (float)o);
				float perlinSample = glm::perlin(glm::vec2((float)x, (float)y) * scale * freq) * 0.5f + 0.5f;
				perlinData[y * dims + x] += perlinSample * amplitude;
				amplitude *= persistence;
			}
		}
	}

	return perlinData;
}
