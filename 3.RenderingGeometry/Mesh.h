#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glm\ext.hpp>

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void create_buffers();
	void initialize(std::vector<Vertex> &verts, std::vector<unsigned int> &indices);
	void bind();
	void unbind();

	unsigned int index_count;
	unsigned int vertex_count;

	// generate vertices and indices of the teacher given geometry
	void makeGeometry();

	// set value methods
	void setVertices(std::vector<Vertex>);
	void setIndices(std::vector<unsigned int>);

	// get value methods
	std::vector<Vertex> getVertices();
	std::vector<unsigned int> getIndices();

private:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
};

