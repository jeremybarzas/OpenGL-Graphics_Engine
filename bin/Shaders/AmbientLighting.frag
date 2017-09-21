#version 410

out vec4 FragColor;

in vec4 vPosition;
in vec4 vNormal;
in vec4 vColor;

void main()
{
	vec3 UP = normalize(vec3(0, 1, 0));
	vec3 N = normalize(vNormal.xyz);
	float NdotUP = dot(N, UP);
	float influence = NdotUP + 0.5 * 0.5;

	vec4 Ka = vColor;	
	vec4 Ia = vec4(1, 1, 1, 1);	
	
	vec4 hemisphere = mix(Ia, Ka, influence);
    FragColor = hemisphere;
}