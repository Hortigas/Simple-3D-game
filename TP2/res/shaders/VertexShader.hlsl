#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexCoords;
layout(location = 3) in vec3 vertexOffset;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec4 FragPosLightSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	FragPos = vec3(model * vec4(vertexPosition + vertexOffset, 1.0));
	Normal = mat3(transpose(inverse(model))) * vertexNormal;
	TexCoords = vertexTexCoords;
	gl_Position = projection * view * vec4(FragPos, 1.f);
}