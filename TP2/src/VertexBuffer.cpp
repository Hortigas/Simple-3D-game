#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &Renderer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, Renderer_ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &Renderer_ID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, Renderer_ID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::define(const void * data, unsigned int size)
{
	glGenBuffers(1, &Renderer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, Renderer_ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
