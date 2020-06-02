#pragma once
#include <GL/glew.h>

class VertexBuffer
{
private:
	unsigned int Renderer_ID;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	void define(const void* data, unsigned int size);
};

