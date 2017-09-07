#pragma once
#include <Application.h>
#include "Camera.h"
#include "Gizmos.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm\glm.hpp>


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

	// to be placed elsewhere later
	std::vector<glm::vec4> generateHalfCircle(float, unsigned int);
	std::vector<glm::vec4> rotatePoints(std::vector<glm::vec4>, unsigned int);
	
	// to be used later
	std::vector<unsigned int> assignIndices(std::vector<glm::vec4>, unsigned int);
};

