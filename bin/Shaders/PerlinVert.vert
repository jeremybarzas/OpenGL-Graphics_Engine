#version 410

layout(location=0) in vec4 position;
layout(location=3) in vec2 uv;

out vec2 vUv;

uniform mat4 projectionViewWorld;

void main() 
{	
	vUv = uv;
	gl_Position = projectionViewWorld * position;
}