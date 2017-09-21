#version 410

out vec4 FragColor;

in vec4 vPosition;
in vec4 vNormal;
in vec4 vColor;

uniform float specularPower;
uniform vec4 cameraPosition;

void main()
{
	vec3 L = vec3(1, -1, 0);

	vec3 N = normalize(vNormal.xyz);

	vec3 R = reflect(normalize(L), N);

	vec3 V = normalize(cameraPosition.xyz - vPosition.xyz);	
	
	float RdotV = dot(R, V);
	
	float influence = max(RdotV, 0);

	float attenuation = pow(influence, specularPower);
	
	vec4 Is = vec4(1,1,1,1);	
	vec4 Ks = vec4(1,1,1,1);

	vec4 specular = Ks * attenuation * Is;
    FragColor = specular;
}