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
	vec4 top = vec4(.25, .25, 1, 1);
	vec4 bot = vec4(0, 1, 0, 1);
	vec4 hemisphere = mix(bot, top, influence);
    FragColor = hemisphere;
}