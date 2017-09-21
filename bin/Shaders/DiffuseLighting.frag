#version 410

out vec4 FragColor;

in vec4 vPosition;
in vec4 vNormal;
in vec4 vColor;

void main()
{
	vec4 lightDirection = vec4(1, 1, 0, 1);	
	vec4 lightColor = vec4(0.75, .75, 0.60, 1);
	float LdotN = dot(lightDirection, vNormal);
	vec4 diffuse = vColor * LdotN * lightColor;
    FragColor = diffuse;
}