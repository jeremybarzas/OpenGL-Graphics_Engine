#version 410

out vec4 FragColor;

in vec4 vPosition;
in vec4 vNormal;
in vec4 vColor;

uniform float lightDirX;
uniform float lightDirY;
uniform float lightDirZ;
uniform float sphereColorR;
uniform float sphereColorG;
uniform float sphereColorB;
uniform float sphereColorA;
uniform float specularPower;
uniform vec4 cameraPosition;

void main()
{
	vec3 L = normalize(vec3(lightDirX, lightDirY, lightDirZ));
	vec3 N = normalize(vNormal.xyz);

	// ambient
	vec4 Ka = vec4(0);	
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
	vec3 V = normalize(cameraPosition.xyz - vPosition.xyz);
	vec3 H = normalize(-L + V);
	float HdotN = dot(H, N);	
	float influence = max(0, HdotN);
	float attenuation = pow(influence, specularPower);
	vec4 specular = Ks * attenuation * Is;
    
	vec4 blinnPhong = ambient + diffuse + specular;
	FragColor = blinnPhong;

	vec4 meshColor = vec4(sphereColorR, sphereColorG, sphereColorB, 1);
	FragColor += meshColor * .5;
}