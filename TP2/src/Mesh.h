#pragma once
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "VertexArray.h"
#include "Shader.h"	
#include "MVP.h"

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};
struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
private:
	unsigned int VBO, EBO;
	VertexArray VAO;
	void setupMesh();
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
};

