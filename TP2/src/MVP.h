#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "Shader.h"

class MVP
{
public:
	int pos;
	glm::mat4 MVPMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	MVP();
	~MVP();
	void defineModelMatrix(float scale, float x, float y, float z, float angX, float angY, float angZ);
	void rotate(float ang, glm::vec3 vetor);
	void rotateX(float ang);
	void rotateY(float ang);
	void rotateZ(float ang);
	void scale(float valor);
	void translate(glm::vec3 vector);
	void translateX(float unit);
	void translateY(float unit);
	void translateZ(float unit);
	void defineViewMatrix(int X, int Y, int Z, int lookX, int lookY, int lookZ, int UPpos);
	void defineProjectionMatrix(float fov);
	void createMVPMatrix();
	void use(Shader shader);
	void resetModel();
	void resetView();
	void resetProjection();
};

