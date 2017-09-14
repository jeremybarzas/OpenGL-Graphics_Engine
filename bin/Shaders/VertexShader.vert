#version 410

layout(location=0) in vec4 position;
layout(location=1) in vec4 color;
layout(location=2) in vec4 normal;
layout(location=3) in vec4 UV;

out vec4 vPositon;
out vec4 vColor;
out vec4 vNormal;
out vec4 vUv;

uniform mat4 projectionViewWorld;
uniform vec4 ka;
uniform vec4 kd;
uniform vec4 ks;

void main() 
{
	vColor = color;
	gl_Position = projectionViewWorld * position;
}