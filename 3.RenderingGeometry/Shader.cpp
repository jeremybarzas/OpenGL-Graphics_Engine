#include "Shader.h"
#include <gl_core_4_4.h>
#include <string>
#include <fstream>

Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::bind()
{
	// use given shader program
	glUseProgram(m_program);
}

void Shader::unbind()
{
	// clear shader program
	glUseProgram(0);
}

void Shader::load(const char * filename, unsigned int type)
{
	std::ifstream in(filename);
	std::string line, contents;		

	// while file is not empty
	while (std::getline(in, line))
	{	
		//add that line to the total contents
		contents += line + "\n";	
	}

	// convert to a c-string
	const char * data = contents.c_str();	

	switch (type)
	{
	case GL_VERTEX_SHADER:
		vsSource = data;
		m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vertexShader, 1, (const char **)&vsSource, 0);
		glCompileShader(m_vertexShader);

	case GL_FRAGMENT_SHADER:
		fsSource = data;
		m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_fragmentShader, 1, (const char **)&fsSource, 0);
		glCompileShader(m_fragmentShader);	
	}
}

void Shader::attach()
{
	m_program = glCreateProgram();
	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);
	
	int success = GL_FALSE;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
	glDeleteShader(m_fragmentShader);
	glDeleteShader(m_vertexShader);
}

void Shader::defaultLoad()
{
	// ========== Create Shaders ==========
	vsSource = "#version 410\n \
							layout(location=0) in vec4 position; \
							layout(location=1) in vec4 colour; \
							out vec4 vColour; \
							uniform mat4 projectionViewWorldMatrix; \
							void main() { vColour = colour; gl_Position = projectionViewWorldMatrix * position; }";

	fsSource = "#version 410\n \
							in vec4 vColour; \
							out vec4 fragColor; \
							void main() { fragColor = vColour; }";

	// ========== Complie Shaders ==========
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_vertexShader, 1, (const char **)&vsSource, 0);
	glCompileShader(m_vertexShader);
	glShaderSource(m_fragmentShader, 1, (const char **)&fsSource, 0);
	glCompileShader(m_fragmentShader);
}

unsigned int Shader::getUniform(const char* name)
{		
	return glGetUniformLocation(m_program, name);
}

