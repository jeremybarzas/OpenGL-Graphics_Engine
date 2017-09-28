#version 410

out vec4 FragColor;

in vec4 vPosition;
in vec4 vNormal;
in vec4 vColor;

uniform vec4 cameraPosition;
uniform float lightDirX ;
uniform float lightDirY;
uniform float lightDirZ;
uniform float specularPower;

void main()
{
	vec3 L = normalize(vec3(1, -1, 0));
	vec3 N = normalize(vNormal.xyz);

	// ambient
	vec4 Ka = vec4(1);	
	vec4 Ia = vec4(1);
	vec4 ambient = Ka * Ia;

	// diffuse
	vec4 Kd = vec4(1);
	vec4 Id = vec4(1);
	float LdotN = max(0, dot(-L, N));
	vec4 diffuse = Kd * LdotN * Id;

	// specular
	vec4 Ks = vec4(1);
	vec4 Is = vec4(1);
	vec3 R = reflect(L, N);
	vec3 V = normalize(cameraPosition.xyz - vPosition.xyz);
	float RdotV = dot(R, V);	
	float influence = max(0, RdotV);
	float attenuation = pow(influence, specularPower);
	vec4 specular = Ks * attenuation * Is;
    
	vec4 phong = ambient + diffuse + specular;
	FragColor = phong;
}