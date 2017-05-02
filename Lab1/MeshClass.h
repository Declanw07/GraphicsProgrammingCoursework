#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "obj_loader.h"

class Vertex
{

public:

	Vertex(const glm::vec3& position, const glm::vec2& texCoordinate){

		this->position = position;
		this->texCoordinate = texCoordinate;
		this->normal = normal;

	}

	glm::vec3* GetPosition(){ return &position; }
	glm::vec2* GetTexCoordinate(){ return &texCoordinate; }
	glm::vec3* GetNormal(){ return &normal; }

	glm::vec3 position;
	glm::vec2 texCoordinate;
	glm::vec3 normal;

private:



};

class Mesh
{
public:

	Mesh();
	Mesh(Vertex* verts, unsigned int vertCount);
	~Mesh();

	void RenderMesh();
	void initialise(Vertex* verts, unsigned int vertCount, unsigned int* indices, unsigned int indiceCount);
	void loadModel(const std::string& modelName);
	void initialiseModel(const IndexedModel& model);

private:

	enum{

		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS

	};

	GLuint VAO;
	GLuint vertArrayBuffers[NUM_BUFFERS];
	unsigned int drawCount;

};
