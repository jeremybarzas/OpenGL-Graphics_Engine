#version 410

layout(location=0) in vec4 position;
layout(location=1) in vec4 color;
layout(location=2) in vec4 normal;
layout(location=3) in vec2 uv;

out vec4 vPosition;
out vec4 vColor;
out vec4 vNormal;
out vec2 vUv;

uniform mat4 projectionViewWorld;

void main() 
{
	vPosition = position;
	vColor = color;
	vNormal = normal;
	vUv = uv;
	gl_Position = projectionViewWorld * position;
}