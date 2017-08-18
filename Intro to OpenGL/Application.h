#pragma once
struct  GLFWwindow;
class Application
{
public:
	Application();
	virtual ~Application();
	void run(const char*, unsigned int, unsigned int, bool);

protected:
	virtual void startup() = 0;
	virtual void shutdown() = 0;
	virtual void update(float) = 0;
	virtual void draw() = 0;
	bool m_gameover;
	GLFWwindow* m_window;
};
