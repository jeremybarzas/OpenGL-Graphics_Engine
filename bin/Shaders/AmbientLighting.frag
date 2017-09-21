#version 410

out vec4 FragColor;

in vec4 vPosition;
in vec4 vNormal;
in vec4 vColor;

void main()
{
	vec4 UP = vec4(0, 1, 0, 1);
	float NdotUP = dot(vNormal, UP);
	float influence = NdotUP + 0.5 * 0.5;
	vec4 lightColor = vec4(0.75, .75, 0.60, 1);	
	vec4 hemisphere = mix(lightColor, vColor, influence);
    FragColor = hemisphere;
}