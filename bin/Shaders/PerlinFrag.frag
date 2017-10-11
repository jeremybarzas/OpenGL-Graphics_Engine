#version 410

in vec2 vUv;

out vec4 fragColor;

uniform sampler2D perlinTexture;

void main() 
{ 
	fragColor = texture(perlinTexture, vUv).rrrr;
	fragColor.a = 1;
}