#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>

struct Vertex 
{
	glm::vec4 position;
	glm::vec4 color;	
};

void generateGrid(unsigned int rows, unsigned int cols)
{
	Vertex* vertArray = new Vertex[rows * cols];
	
	for (unsigned int r = 0; r < rows; ++r)
	{
		for(unsigned int c = 0; c < cols; ++c)
		{
			vertArray[r * cols + c].position = glm::vec4((float)c, 0, (float)r, 1);

			glm::vec3 color = glm::vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))));
			vertArray[r * cols + c].color = glm::vec4(color, 1);			
		}
	}
	delete[] vertArray;
}

