#pragma once

class Application
{
public:
	Application();
	virtual ~Application();
	void run(float width, float height, const char* title, bool fullscreen);

protected:
	virtual void startup() = 0;
	virtual void update(float) = 0;
	virtual void draw() = 0;
	virtual void shutdown() = 0;
};

