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
	glBindVertexArray(this->m_vao);

	// bind Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
		
	// buffer the Vertex Buffer Object's data
	glBufferData(GL_ARRAY_BUFFER, this->m_vertex_count * sizeof(Vertex), this->m_vertices.data(), GL_STATIC_DRAW);
	
	// bind Index Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo);
		
	// buffer the Index Buffer Object's data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_index_count * sizeof(unsigned int), this->m_indices.data(), GL_STATIC_DRAW);
	
	// enable and assign vertex attribute array index 0
	//position
	glEnableVertexAttribArray(0);	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);


	// enable and assign vertex attribute array index 1
	//color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4)));

	//noramls
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 2));
	// ========== Cleanup ==========
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
		this->m_vertices.push_back(v);

	// assign the vertex count
	this->m_vertex_count = m_vertices.size();

	// populate index array with passed values
	for (auto i : indices)
		this->m_indices.push_back(i);

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

