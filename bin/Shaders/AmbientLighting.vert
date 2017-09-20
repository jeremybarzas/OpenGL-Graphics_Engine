#version 410

layout(location=0) in vec4 position;
layout(location=1) in vec4 color;
layout(location=2) in vec4 normal;

uniform mat4  projectionViewWorld;
out vec4 vPosition;
out vec4 vNormal;
out vec4 vColor;
void main()
{
    vColor = color;
    vNormal = normal;
    vPosition = position;
    gl_Position = projectionViewWorld * position;
}