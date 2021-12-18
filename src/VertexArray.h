#pragma once

class VertexArray
{
public:
	VertexArray(
		const float* verts,
		unsigned int numVerts,
		unsigned int numVertElements,
		const unsigned int* indices,
		unsigned int numIndices
	);

	~VertexArray();

	void SetActive();

	unsigned int GetNumVerts() const { return mNumVerts; }
	unsigned int GetNumIndices() const { return mNumIndices; }

private:
	unsigned int mNumVerts;
	unsigned int mNumIndices;
	unsigned int mVertexBufferID;
	unsigned int mIndexBufferID;
	unsigned int mVertexArrayID;
};