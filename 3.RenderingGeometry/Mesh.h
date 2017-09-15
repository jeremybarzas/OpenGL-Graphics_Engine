#pragma once
#include <vector>
#include <glm\glm.hpp>

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;	
	glm::vec4 normal;
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

private:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Vertex> m_color;
	std::vector<Vertex> m_normals;	
};

