#pragma once

#include <iostream>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <SOIL2.h>

#include "Shader.h"
#include "Mesh.h"
#include "MVP.h"

using namespace std;

static unsigned int TextureFromFile(const char *path, const string &directory)
{
	bool gamma = false;
	string filename = string(path);
	filename = directory + '/' + filename;
	std::cout <<"Texturas: " <<filename;

	if (path[7] == '7')
		filename = "res/objects/havoc/Tex_0007_3.tga";
	if (path[7] == '6')
		filename = "res/objects/havoc/Tex_0006_1.tga";

	unsigned int textureID;
	int width, height;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *data = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	if (0 == data) {
		std::cout << " ERROR\n";
		std::cout << "SOIL loading error: " << SOIL_last_result();
		std::cout << "\n";
	}
	else {
		std::cout << " OK\n";
	}
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(data);

	return textureID;
}



class Model
{
public:
	// Variables
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;
	// Functions   
	Model(string const &path);
	void Draw(Shader shader);
	void DrawVeiculo(Shader shader, MVP &mvp, float deltaTime);
private:
	// Variables
	float anguloDaElice;
	// Functions
	void loadModel(string const &path);
	void processNode(aiNode * node, const aiScene * scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		string typeName);
};

