#version 410

out vec4 FragColor;

in vec4 vPosition;
in vec4 vNormal;
in vec4 vColor;

void main()
{
	vec3 L = normalize(vec3(1, -1, 0));
	vec3 N = normalize(vNormal.xyz);	
	float LdotN = dot(-L, N);

	vec4 Kd = vec4(1);
	vec4 Id = vec4(1);	

	vec4 diffuse = Kd * LdotN * Id;
    FragColor = diffuse;
}