#version 410

out vec4 FragColor;

in vec4 vPosition;
in vec4 vNormal;
in vec4 vColor;
in vec2 vUv;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform float lightDirX;
uniform float lightDirY;
uniform float lightDirZ;
uniform float specularPower;
uniform vec4 cameraPosition;

// texture sampler
uniform sampler2D sampler;

void main()
{		
	vec3 L = normalize(vec3(lightDirX, lightDirY, lightDirZ));
	vec3 N = normalize(vNormal.xyz);

	// ambient
	vec4 Ka = vec4(1);	
	vec4 Ia = vec4(1);
	vec4 ambient = Ka * Ia;
	ambient.xyz *= ambientStrength;

	// diffuse
	vec4 Kd = vec4(1);
	vec4 Id = vec4(1);
	float LdotN = max(0, dot(-L, N));
	vec4 diffuse = Kd * LdotN * Id;
	diffuse.xyz *= diffuseStrength;

	// specular
	vec4 Ks = vec4(1);
	vec4 Is = vec4(1);	
	vec3 V = normalize(cameraPosition.xyz - vPosition.xyz);
	vec3 H = normalize(-L + V);
	float HdotN = dot(H, N);	
	float influenceS = max(0, HdotN);
	float attenuation = pow(influenceS, specularPower);
	vec4 specular = Ks * attenuation * Is;
    specular.xyz *= specularStrength;

	vec4 blinnPhong = ambient + diffuse + specular;

	FragColor = texture(sampler, vUv);	
	FragColor *= blinnPhong;
}