#pragma once
#define quantidade 30
#define quantObjetos 20

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Veiculo.h"
#include "MVP.h"
#include "Model.h"

struct coords {
	int x;
	int z;
};

struct chunk
{
	bool Use = false;
	int x;
	int z;
	int randX[quantObjetos];
	int randZ[quantObjetos];
	int type[quantObjetos];
	float rotation[quantObjetos];
};

class Terrain
{
private:
	chunk loadedChunks[9];
	float X, Y, Z;
	glm::vec3 translations[quantidade*quantidade];
	float *quadVertices;
	void loaderPos();
public:
	VertexBuffer transVB, posVB;
	VertexArray posVA;
	void loaderChunks();
	void draw(Shader shader, Veiculo veiculo, MVP mvp, Model model[],unsigned int texture);
	void calculateObjects(int Hx, int Hz, MVP mvp);
	Terrain();

};

