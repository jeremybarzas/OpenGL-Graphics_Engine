#version 410

layout(location=0) in vec4 position;
layout(location=2) in vec4 normal;
layout(location=3) in vec2 uv;

out vec2 vUv;

uniform mat4 projectionViewWorld;

uniform sampler2D perlinTexture;

void main() 
{
	vec4 pos = position;
	pos.y += texture(perlinTexture, uv).r * 5;
	
	//vec3 disp = vNormal.xyz * (vPosition.y + texture(perlinTexture, uv).r);
	//vPosition = vec4(vPosition.xyz + disp, 1);

	vUv = uv;
	gl_Position = projectionViewWorld * pos;
}