#include "MeshClass.h"
#include <vector>

Mesh::Mesh(){

	drawCount = NULL;

}

void Mesh::initialise(Vertex* verts, unsigned int vertCount, unsigned int* indices, unsigned int indiceCount){

	IndexedModel model;

	for (unsigned int i = 0; i < vertCount; i++){

		model.positions.push_back(*verts[i].GetPosition());
		model.texCoords.push_back(*verts[i].GetTexCoordinate());

	}

	for (unsigned int i = 0; i < indiceCount; i++){

		model.indices.push_back(indices[i]);

	}

	initialiseModel(model);

}

void Mesh::initialiseModel(const IndexedModel& model){

	drawCount = model.indices.size();

	glGenVertexArrays(1, &VAO); // Create a vertex array and store in VAO.
	glBindVertexArray(VAO); // Bind VAO.

	glGenBuffers(NUM_BUFFERS, vertArrayBuffers); // Create buffers.

	glBindBuffer(GL_ARRAY_BUFFER, vertArrayBuffers[POSITION_VERTEXBUFFER]); // Identify type and pass data.
	glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); // Move data to GPU.

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertArrayBuffers[TEXCOORD_VB]); // Identify type and pass data.
	glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); // Move data to GPU.

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertArrayBuffers[NORMAL_VB]); // Identify type and pass data.
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0])*model.normals.size(), &model.normals[0], GL_STATIC_DRAW); // Move data to GPU.

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertArrayBuffers[INDEX_VB]); // Identify type and pass data.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size()*sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); // Move data to GPU.

	glBindVertexArray(0);

}

void Mesh::loadModel(const std::string& modelName){

	IndexedModel model = OBJModel(modelName).ToIndexedModel();

	initialiseModel(model);

}



Mesh::Mesh(Vertex* verts, unsigned int vertCount){

	drawCount = vertCount; // Quanitity of vertices.

	std::vector<glm::vec3> positions; // List to hold position data.
	std::vector<glm::vec2> textCoordinates; // List to hold texture coordinates.

	positions.reserve(vertCount); // Reserve the space required to hold the position data.
	textCoordinates.reserve(vertCount); // Reserve the space required to hold the texture coordinates.

	glGenVertexArrays(1, &VAO); // Generate a vertex array and then store it within the VAO.
	glBindVertexArray(VAO); // Bind the VAO.

	for (unsigned int i = 0; i < vertCount; i++){

		positions.push_back(verts[i].position); // Store positions into array.
		textCoordinates.push_back(verts[i].texCoordinate); // Store texture coordinates into array.

	}

	glGenBuffers(NUM_BUFFERS, vertArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertArrayBuffers[POSITION_VERTEXBUFFER]);

	glBufferData(GL_ARRAY_BUFFER, vertCount*sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, vertCount*sizeof(textCoordinates[0]), &textCoordinates[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0); // Unbind the VAO.

}

Mesh::~Mesh(){

	glDeleteVertexArrays(1, &VAO);

}

void Mesh::RenderMesh(){

	glBindVertexArray(VAO);
	/*glDrawArrays(GL_TRIANGLES, 0, drawCount);*/
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

