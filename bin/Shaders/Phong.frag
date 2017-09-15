#version 410
out vec4 FragColor;
in vec4 vPosition;
in vec4 vNormal;
in vec4 vColor;
void main()
{
    FragColor = vNormal;
}