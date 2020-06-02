#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int size)
	:Quantidade(size/sizeof(unsigned int))
{
	glGenBuffers(1, &Renderer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Renderer_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &Renderer_ID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Renderer_ID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::GetQuantidade() const {
	return Quantidade;
}

void IndexBuffer::define(const unsigned int * data, unsigned int size)
	
{
	glGenBuffers(1, &Renderer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Renderer_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	Quantidade = size / sizeof(unsigned int);
}
