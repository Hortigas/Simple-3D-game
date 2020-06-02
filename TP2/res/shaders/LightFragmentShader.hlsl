#version 330 core

out vec3 color;

uniform vec3 lightColor;

void main() {
	color = lightColor;
}