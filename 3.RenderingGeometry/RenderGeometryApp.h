#pragma once
#include <Application.h>
#include "Camera.h"
#include "Gizmos.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm\glm.hpp>

struct Light
{
	float lightDirX = 1;
	float lightDirY = -1;
	float lightDirZ = -1;	
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

	Shader* m_shader;
	Mesh* m_mesh;	
	Light m_light;

	// the texture handles
	unsigned int m_texture;	
	unsigned int m_perlinTexture;

	std::vector<glm::vec4> generateHalfCircle(float, unsigned int);
	std::vector<glm::vec4> rotatePoints(std::vector<glm::vec4>, unsigned int);
	std::vector<unsigned int> genIndicesTriStrip(unsigned int, unsigned int);

	// generate sphere using triangle strips
	void genSphere(float radius, int np, int nm);

	// generate plane using triangle strips
	void genPlane(int width, int length, int dims);

	// generate cube using traingle strips
	void genCube(int width, int length, int dims);

	// generate perlin noise	
	float* perlinNoise(int dims);
};
