#pragma once
#include <vector>
#include <glm\glm.hpp>

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;	
	glm::vec4 normal;
	glm::vec2 uv;
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

	unsigned int m_index_count;
	unsigned int m_vertex_count;

	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;

private:	
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
};

