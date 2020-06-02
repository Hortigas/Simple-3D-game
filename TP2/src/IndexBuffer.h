#pragma once
#include <GL/glew.h>

class IndexBuffer
{
private:
	unsigned int Renderer_ID;
	unsigned int Quantidade;
public:
	IndexBuffer(const unsigned int *data, unsigned int size);
	IndexBuffer();
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetQuantidade() const;
	void define(const unsigned int *data, unsigned int size);
};

