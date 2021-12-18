#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(
	const float* verts,
	unsigned int numVerts,
	unsigned int numVertElements,
	const unsigned int* indices,
	unsigned int numIndices)
  : mNumVerts(numVerts),
	mNumIndices(numIndices)
{
	glGenVertexArrays(1, &mVertexArrayID);
	glBindVertexArray(mVertexArrayID);

	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(
		GL_ARRAY_BUFFER,
		numVerts * numVertElements * sizeof(float),
		verts,
		GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		numIndices * sizeof(int),
		indices,
		GL_STATIC_DRAW);

	// 頂点属性その1: 頂点座標
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, numVertElements * sizeof(float), 0);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteBuffers(1, &mIndexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArrayID);
}