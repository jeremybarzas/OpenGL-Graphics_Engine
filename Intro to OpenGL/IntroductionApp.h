#pragma once
#include "Application.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>

class IntroductionApp :	public Application
{
public:
	IntroductionApp();
	~IntroductionApp();

	// Inherited via Application
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void update(float) override;
	virtual void draw() override;
	
	/**
	runs our application

	@param title the name of the window
	@param width the width of the window
	@param height the height of the window
	@param fullscreen is it fullscreen or not
	*/
	void run(const char*, unsigned int, unsigned int, bool);

	glm::mat4 m_view;
	glm::mat4 m_projection;
};
