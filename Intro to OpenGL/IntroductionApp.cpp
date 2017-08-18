#include "IntroductionApp.h"
#include "Gizmos.h"

IntroductionApp::IntroductionApp()
{
}

IntroductionApp::~IntroductionApp()
{
}

void IntroductionApp::startup()
{
	m_view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	Gizmos::create();
}

void IntroductionApp::shutdown()
{
}

void IntroductionApp::update(float)
{
}

void IntroductionApp::draw()
{		
	// removes all shapes and lines
	Gizmos::clear();

	// creates transform handles
	Gizmos::addTransform(glm::mat4(1));

	// colors to be used
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);

	// generates a grid of lines
	for (int i = 0; i < 21; ++i) 
	{ 
		Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
						glm::vec3(-10 + i, 0, -10),
						i == 10 ? white : black);

		Gizmos::addLine(glm::vec3(10, 0, -10 + i),
						glm::vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}	
		
	// draws the current gizmo buffers
	Gizmos::draw(m_projection * m_view);		
}

void IntroductionApp::run(const char *, unsigned int, unsigned int, bool)
{
}
