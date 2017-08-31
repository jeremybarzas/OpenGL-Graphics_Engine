#pragma once
#include <Application.h>
#include "Camera.h"
#include "Gizmos.h"

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;
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
	
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int m_programID;	

	void generateGrid(unsigned int rows, unsigned int cols);	
};

