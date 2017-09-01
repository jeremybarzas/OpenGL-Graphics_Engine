#include "Mesh.h"
#include <gl_core_4_4.h>



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::create_buffers()
{
	// ========== Generate Buffer Objects ==========
	// generate Vertex Buffer Object
	glGenBuffers(1, &m_vbo);

	// generate Index Buffer Object
	glGenBuffers(1, &m_ibo);

	// generate Vertex Array Object
	glGenVertexArrays(1, &m_vao);
}

void Mesh::initialize(std::vector<Vertex>& verts, std::vector<unsigned int>& indices)
{
	setVertices(verts);
	setIndices(indices);
}

void Mesh::bind()
{
	// ========== Bind Buffer Objects ==========
	// bind Vertex Array Object
	glBindVertexArray(m_vao);

	// bind Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// bind Index Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void Mesh::unbind()
{
	// ========== Cleanup Buffer Objects ==========
	// clear the Vertex Array Object bind
	glBindVertexArray(0);

	// clear the Vertex Buffer Object bind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// clear the Index Buffer Object bind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::makeGeometry()
{
	Vertex a = { glm::vec4(-5,  0, 0, 1)		, glm::vec4(.1, .1, .1, 1) }; //bottom left	
	Vertex b = { glm::vec4(5,  0, 0, 1)			, glm::vec4(.1, .1, .1, 1) }; //bottom right
	Vertex c = { glm::vec4(5, -5, 0, 1)			, glm::vec4(.1, .1, .1, 1) }; //top left
	Vertex d = { glm::vec4(-5, -5, 0, 1)		, glm::vec4(1, 0, 0, 1) }; //top right
	Vertex e = { glm::vec4(-5,  5, 0, 1)		, glm::vec4(0, 0, 1, 1) }; //top right	

	std::vector<Vertex> vertices{ a,b,c,d,e };
	std::vector<unsigned int> indices{ 0, 1, 2, 0, 2, 3, 0, 4, 1 };

	initialize(vertices, indices);
}

void Mesh::setVertices(std::vector<Vertex> vertices)
{
	m_vertices = vertices;
}

void Mesh::setIndices(std::vector<unsigned int> indices)
{
	m_indices = indices;
}

std::vector<Vertex> Mesh::getVertices()
{
	return m_vertices;
}

std::vector<unsigned int> Mesh::getIndices()
{
	return m_indices;
}
