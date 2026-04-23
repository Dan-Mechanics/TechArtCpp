#version 460 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;

out vec3 vColor;
out vec3 FragPos;

void main() {
	gl_Position = vec4(Pos, 1.0f);
	vColor = Color;
	FragPos = Pos;
}