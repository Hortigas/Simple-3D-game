#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>
#include <SOIL2.h>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

class SkyBox
{
public:
	VertexArray VA;
	VertexBuffer VB;
	unsigned int textureID;
	float *skyboxVertices;
	std::vector<std::string> faces;
	
	unsigned int cubemapTexture;

	SkyBox();
	unsigned int loadCubemap(std::vector<std::string> faces);

	void draw();

	void loader();

};

