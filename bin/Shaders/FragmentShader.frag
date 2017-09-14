#version 410

in vec4 vColor;
in vec4 vPositon;
in vec4 vNormal;
in vec4 vUv;

out vec4 fragColor;

void main() 
{
	fragColor = vColor; 
}