#version 410

layout(location=0) in vec4 position;
layout(location=1) in vec4 color;
layout(location=2) in vec4 normal;
//the layout locations are the map of the Vertex that is buffered
//the 0 is size 4floats it is at address 0 relative to this Vertex
//the 1 is size 4 floats it is at address 0 + size 4 floats
//the 2 is size 4 floats it is at address 0 + size 4 floats + size 4 floats

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