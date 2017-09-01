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
	// ========== Generate Objects ==========
	// generate Vertex Array Object
	glGenVertexArrays(1, &m_vao);

	// generate Vertex Buffer Object
	glGenBuffers(1, &m_vbo);

	// generate Index Buffer Object
	glGenBuffers(1, &m_ibo);	

	// ========== Bind Objects ==========
	// bind Vertex Array Object
	glBindVertexArray(m_vao);

	// bind Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		
	// buffer the Vertex Buffer Object's data
	glBufferData(GL_ARRAY_BUFFER, m_vertex_count * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);	

	// bind Index Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		
	// buffer the Index Buffer Object's data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_count * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
	
	// enable and assign vertex attribute array index 0
	glEnableVertexAttribArray(0);	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// enable and assign vertex attribute array index 1
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4)));

	// clear the Vertex Array Object bind
	glBindVertexArray(0);

	// clear the Vertex Buffer Object bind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// clear the Index Buffer Object bind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::initialize(std::vector<Vertex>& verts, std::vector<unsigned int>& indices)
{
	// populate vertex array with passed values
	for (auto v : verts)
		m_vertices.push_back(v);

	// assign the vertex count
	this->m_vertex_count = m_vertices.size();

	// populate vertex array with passed values
	for (auto i : indices)
		m_indices.push_back(i);

	// assign the index count
	this->m_index_count = m_indices.size();
}

void Mesh::bind()
{
	// bind the vertex array object
	glBindVertexArray(this->m_vao);
}

void Mesh::unbind()
{	
	// clear the Vertex Array Object bind
	glBindVertexArray(0);	
}

void Mesh::meshStartup()
{
	// populate vert and index arrays
	Vertex a = { glm::vec4(-5,  0, 0, 1)		, glm::vec4(.1, .1, .1, 1) }; //bottom left	
	Vertex b = { glm::vec4(5,  0, 0, 1)			, glm::vec4(.1, .1, .1, 1) }; //bottom right
	Vertex c = { glm::vec4(5, -5, 0, 1)			, glm::vec4(.1, .1, .1, 1) }; //top left
	Vertex d = { glm::vec4(-5, -5, 0, 1)		, glm::vec4(1, 0, 0, 1) }; //top right
	Vertex e = { glm::vec4(-5,  5, 0, 1)		, glm::vec4(0, 0, 1, 1) }; //top right	

	std::vector<Vertex> vertices{ a,b,c,d,e };
	std::vector<unsigned int> indices{ 0, 1, 2, 0, 2, 3, 0, 4, 1 };
		
	this->initialize(vertices, indices);

	this->create_buffers();	
}

void Mesh::meshDraw()
{
	this->bind();
	// set to draw wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// draws each element
	glDrawElements(GL_TRIANGLES, this->m_index_count, GL_UNSIGNED_INT, 0);

	// unbind vertex array
	this->unbind();
}

