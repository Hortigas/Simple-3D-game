#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &VAO_ID);
	glBindVertexArray(VAO_ID);
}
VertexArray::~VertexArray()
{
}
void VertexArray::Bind()
{
	glBindVertexArray(VAO_ID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
