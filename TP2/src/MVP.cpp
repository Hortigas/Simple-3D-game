#include "MVP.h"
#include <iostream>

MVP::MVP()
{
	ModelMatrix = glm::mat4(1.f);;
	ViewMatrix = glm::mat4(1.f);
	ProjectionMatrix = glm::mat4(1.f);
	defineProjectionMatrix(45.f);
}

MVP::~MVP()
{
}

void MVP::defineModelMatrix(float scale, float x, float y, float z, float angX, float angY, float angZ)
{
	glm::mat4 Model = glm::mat4(1.f);
	Model = glm::translate(Model, glm::vec3(x, y, z));
	Model = glm::rotate(Model, glm::radians(angX), glm::vec3(1.f, 0  , 0  ));
	Model = glm::rotate(Model, glm::radians(angY), glm::vec3(0  , 1.f, 0  ));
	Model = glm::rotate(Model, glm::radians(angZ), glm::vec3(0  , 0  , 1.f));
	Model = glm::scale(Model, glm::vec3(scale));
	ModelMatrix = Model;
}

void MVP::rotate(float ang, glm::vec3 vetor)
{
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(ang), vetor);
}

void MVP::rotateX(float ang) 
{
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(ang), glm::vec3(1.f, 0, 0));
}

void MVP::rotateY(float ang) 
{
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(ang), glm::vec3(0, 1.f, 0));
}

void MVP::rotateZ(float ang)
{
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(ang), glm::vec3(0, 0, 1.f));
}

void MVP::scale(float valor)
{
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(valor));
}

void MVP::translate(glm::vec3 vector) 
{
	ModelMatrix = glm::translate(ModelMatrix, vector);
}

void MVP::translateX(float unit) 
{
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(unit, 0, 0));
}

void MVP::translateY(float unit) 
{
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, unit, 0));
}

void MVP::translateZ(float unit) 
{
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, 0, unit));
}



void MVP::defineViewMatrix(int x, int y, int z, int lookX, int lookY, int lookZ, int UPpos)
{
	pos = UPpos;
	ViewMatrix = glm::lookAt(
		glm::vec3(x, y, z),
		glm::vec3(lookX, lookY, lookZ),
		glm::vec3(0, UPpos, 0) 
	);
}

void MVP::defineProjectionMatrix(float fov)
{
	glm::mat4 Projection = glm::perspective(glm::radians(fov), 1920.f/1080.f, 0.1f, 500.0f);
	ProjectionMatrix = Projection;
}

void MVP::createMVPMatrix()
{
	MVPMatrix = ProjectionMatrix * ViewMatrix * ModelMatrix;
}

void MVP::use(Shader shader) 
{
	createMVPMatrix();
	shader.setMat4("model", ModelMatrix);
	shader.setMat4("view", ViewMatrix);
	shader.setMat4("projection", ProjectionMatrix);
}

void MVP::resetModel() 
{
	ModelMatrix = glm::mat4(1.f);
}

void MVP::resetView()
{
	ViewMatrix = glm::mat4(1.f);
}

void MVP::resetProjection()
{
	ProjectionMatrix = glm::mat4(1.f);
}

