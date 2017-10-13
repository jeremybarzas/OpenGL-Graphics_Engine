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

uniform sampler2D perlinTexture;

void main() 
{	
	vPosition = position;
	
	vColor = color;
	vNormal = normal;

	vUv = uv;
	vec3 disp = vNormal.xyz * (vPosition.y + texture(perlinTexture, uv).r);
	vPosition = vec4(vPosition.xyz + disp, 1);

	gl_Position = projectionViewWorld * vPosition;
}