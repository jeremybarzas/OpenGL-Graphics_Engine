#version 410

out vec4 FragColor;

in vec4 vPosition;
in vec4 vNormal;
in vec4 vColor;

uniform vec4 cameraPosition;

void main()
{
	vec4 lightDirection = vec4(1, 1, 0, 1);	
	vec4 lightColor = vec4(.75, .75, .60, 1);	
	vec4 reflectedRay = reflect(lightDirection, vNormal);	
	vec4 V = cameraPosition;
	float RdotV = dot(reflectedRay, V);	
	float specularPower = 1;

	for(int i = 0; i < specularPower; i++)
	{
		RdotV = RdotV * RdotV;
	}
	
	vec4 specular = vColor * RdotV * lightColor;
    FragColor = specular;
}