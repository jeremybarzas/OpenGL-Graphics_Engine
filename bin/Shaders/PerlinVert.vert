#version 410

layout(location=0) in vec4 position;
layout(location=3) in vec2 uv;

out vec2 vUv;

uniform mat4 projectionViewWorld;

uniform sampler2D perlinTexture;

void main() 
{	
	vec4 pos = position;
	pos.y += texture(perlinTexture, uv).r * 5;

	vUv = uv;
	gl_Position = projectionViewWorld * pos;
}