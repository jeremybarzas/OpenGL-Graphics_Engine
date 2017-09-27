#pragma once
#include <Application.h>
#include "Camera.h"
#include "Gizmos.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm\glm.hpp>

// texture
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master\stb_image.h"

struct Light
{
	float lightDirX = 1;
	float lightDirY = -1;
	float lightDirZ = 0;	
	float ambientStrength = 1;
	float diffuseStrength = 1;
	float specularStrength = 1;
	float specularPower = 64;
};


class RenderGeometryApp : public Application
{
public:
	RenderGeometryApp();
	~RenderGeometryApp();	

	// Inherited via Application
	virtual void startup() override;
	virtual void update(float) override;
	virtual void draw() override;
	virtual void shutdown() override;

	Camera* m_camera;
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;	

	Mesh* m_mesh;
	Shader* m_shader;
	Light m_light;

	unsigned int m_texture;

	float m_radius = 1;
	int m_np = 3;
	int m_nm = 4;

	float m_prev_radius;
	int m_prev_np;
	int m_prev_nm;

	std::vector<glm::vec4> generateHalfCircle(float, unsigned int);
	std::vector<glm::vec4> rotatePoints(std::vector<glm::vec4>, unsigned int);
	std::vector<unsigned int> genIndicesTriStrip(unsigned int, unsigned int);
	
	// generate a sphere using triangles
	void genSphereTriangles(unsigned int, unsigned int, unsigned int&, unsigned int&, unsigned int&, unsigned int&);

	void genSphere();
};

