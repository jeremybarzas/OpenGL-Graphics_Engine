#version 410

out vec4 FragColor;

in vec4 vPosition;
in vec4 vNormal;
in vec4 vColor;

uniform float specularPower;
uniform vec4 cameraPosition;

void main()
{
	vec4 lightDirection = vec4(1, 1, 0, 1);	
	vec4 lightColor = vec4(1, 1, 1, 1);	

	vec4 reflectedRay = reflect(lightDirection, vNormal);		

	vec4 V = normalize(cameraPosition - vPosition);
	
	float RdotV = dot(reflectedRay, V);	
	
	float influence = max(RdotV, 0); 
	
	

	float attenuation = pow(influence, specularPower);
	
	vec4 specular = vColor * attenuation * lightColor;
    FragColor = specular;
}