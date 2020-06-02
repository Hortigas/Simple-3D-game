#include "Terrain.h"

Terrain::Terrain()
{
	X = 2.f;
	Z = 2.f;
	const float metX = X/2.f;
	const float metZ = Z/2.f;
	float Vertices[] = {
		// positions				// normals           // texture coords
		-metX,  0.0f, -metZ,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		 metX,  0.0f, -metZ,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 metX,  0.0f,  metZ,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 metX,  0.0f,  metZ,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		-metX,  0.0f,  metZ,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		-metX,  0.0f, -metZ,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f
	};

	loaderPos();
	loaderChunks();
	posVA.Bind();

	posVB.define(&Vertices[0], sizeof(Vertices));
	//Buffer de vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(0);
	//Buffer de normais
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Buffer de texturas
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	transVB.define(&translations[0], sizeof(translations));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);

	glVertexAttribDivisor(3, 1);
}

void Terrain::loaderPos() {
	int index = 0;
	float v = quantidade / 2.f;
	for (int z = -Z*v; z < Z*v; z += Z)
	{
		for (int x = -X*v; x < X*v; x += X)
		{
			glm::vec3 translation;
			translation.x = x;
			translation.y = 0;
			translation.z = z;
			translations[index++] = translation;
		}
	}
}

void Terrain::loaderChunks() {
	int xeta[9] = { -1,0,1,-1,0,1,-1,0,1 };
	int zeta[9] = { 1,1,1,0,0,0,-1,-1,-1 };
	for (int c = 0; c < 9; c++) {

		loadedChunks[c].Use = true;
		loadedChunks[c].x = xeta[c];
		loadedChunks[c].z = zeta[c];
		for (int r = 0; r < quantObjetos; r++) {
			loadedChunks[c].randX[r] = (rand() % (quantidade * 2)) - quantidade;
			loadedChunks[c].randZ[r] = (rand() % (quantidade * 2)) - quantidade;
			loadedChunks[c].type[r] = rand() % 2;
			loadedChunks[c].rotation[r] = rand() % 360;
		}
	}
}

void Terrain::draw(Shader shader, Veiculo veiculo, MVP mvp, Model model[], unsigned int texture) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shader.Bind();
	shader.setFloat("Material.shininess", 32.f);
	int posX, posZ;
	if (veiculo.Position.x > 0)
		posX = (veiculo.Position.x + quantidade / 2) / (quantidade*X);
	else
		posX = (veiculo.Position.x - quantidade / 2) / (quantidade*X);
	if (veiculo.Position.z > 0)
		posZ = (veiculo.Position.z + quantidade / 2) / (quantidade*Z);
	else
		posZ = (veiculo.Position.z - quantidade / 2) / (quantidade*Z);

	calculateObjects(posX, posZ, mvp);

	for (int c = 0; c < 9; c++)
		for (int p = 0; p < quantObjetos; p++) {
			mvp.resetModel();
			mvp.translate(glm::vec3((loadedChunks[c].x)*quantidade*X, 0, (loadedChunks[c].z)*quantidade*Z));
			mvp.translateX(loadedChunks[c].randX[p]);
			mvp.translateZ(loadedChunks[c].randZ[p]);
			mvp.rotateY(loadedChunks[c].rotation[p]);
			if (loadedChunks[c].type[p] == 0)
				mvp.translateY(-3.1f);
			else if (loadedChunks[c].type[p] == 1)
				mvp.translateY(-5.05f);
			mvp.use(shader);
			model[loadedChunks[c].type[p]].Draw(shader);
		}

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++) {
			mvp.resetModel();
			mvp.translateY(-5.f);
			mvp.translate(glm::vec3((posX + i)*quantidade*X, 0, (posZ + j)*quantidade*Z));
			posVA.Bind();
			mvp.use(shader);
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, quantidade*quantidade);
		}
}

void Terrain::calculateObjects(int Hx, int Hz, MVP mvp) {
	coords coord;
	int i, j, c, r;
	bool notFound;
	int pos;
	vector<coords> newChunks;
	for (c = 0; c < 9; c++)
		loadedChunks[c].Use = false;
	for (i = -1; i <= 1; i++)
		for (j = -1; j <= 1; j++) {
			notFound = true;
			for (c = 0; c < 9; c++)
				if (loadedChunks[c].x == Hx + i && loadedChunks[c].z == Hz + j) {
					loadedChunks[c].Use = true;
					notFound = false;
				}
			if (notFound) {
				coord.x = Hx + i;
				coord.z = Hz + j;
				newChunks.push_back(coord);
			}
		}
	pos = 0;
	for (c = 0; c < 9; c++)
		if (loadedChunks[c].Use == false) {
			loadedChunks[c].x = newChunks[pos].x;
			loadedChunks[c].z = newChunks[pos].z;
			for (r = 0; r < quantObjetos; r++) {
				loadedChunks[c].randX[r] = (rand() % (quantidade * 2)) - quantidade;
				loadedChunks[c].randZ[r] = (rand() % (quantidade * 2)) - quantidade;
				loadedChunks[c].type[r] = rand() % 2;
				loadedChunks[c].rotation[r] = rand() % 360;
			}
			pos++;
		}
}


