#version 460 core

out vec4 FragColor;
in vec3 vColor;
in vec3 FragPos;

void main() {
	vec3 Normal = vec3(0.0f, 0.0f, -1.0f);
	
	// uniforms
	vec3 lightColor = vec3(1.0f);
	vec3 lightPos = vec3(0.5f, 0.5f, 0.0f);
	vec3 viewPos = vec3(0.0f);

	float dist = distance(lightPos, FragPos);
	float strength = max(1.0f - dist * 0.25f, 0.0f);

	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	float shininess = 0.5f;
	float ambient = 0.5f;

	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 8.0f);
	vec3 specular = lightColor * spec;
	
	FragColor = vec4(vColor * specular + vColor * ambient, 1.0f);
}