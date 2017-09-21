#version 410

layout(location=0) in vec4 position;
layout(location=1) in vec4 color;
layout(location=2) in vec4 normal;

out vec4 vPosition;
out vec4 vColor;
out vec4 vNormal;

uniform mat4 projectionViewWorld;

void main() 
{
	vPosition = position;
	vColor = color;
	vNormal = normal;
	gl_Position = projectionViewWorld * position;
}