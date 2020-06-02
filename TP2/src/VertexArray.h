#pragma once
#include <GL/glew.h>

class VertexArray
{
private:
	unsigned int VAO_ID;
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void Unbind();
};

