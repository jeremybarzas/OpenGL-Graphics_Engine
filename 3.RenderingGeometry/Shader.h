#pragma once
class Shader
{
public:
	Shader();
	~Shader();

	void bind();
	void unbind();
	void load(const char*, unsigned int);
	void attach();
	void defaultLoad();
	unsigned int getUniform(const char*);

	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
	const char* m_vsSource;
	const char* m_fsSource;

private:
	unsigned int m_program;
};

