#pragma once
#include "Application.h"

class TestApp :
	public Application
{
public:
	TestApp();
	~TestApp();

	// Inherited via Application
	virtual void startup() override;
	virtual void update(float) override;
	virtual void draw() override;
	virtual void shutdown() override;
};

