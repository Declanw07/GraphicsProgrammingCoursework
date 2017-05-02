#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "CameraClass.h"

struct Transform{

public:

	Transform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)){

		this->position = position;
		this->rotation = rotation;
		this->scale = scale;

	}

	inline glm::mat4 fetchModel() const{

		glm::mat4 positionMat = glm::translate(position);
		glm::mat4 scaleMat = glm::translate(position);
		glm::mat4 rotationX = glm::translate(position);
		glm::mat4 rotationY = glm::translate(position);
		glm::mat4 rotationZ = glm::translate(position);
		glm::mat4 rotationMat = rotationX * rotationY * rotationZ;

		return positionMat * rotationMat * scaleMat;

	}

	inline glm::vec3* GetPosition(){ return &position; }
	inline glm::vec3* GetRotation(){ return &rotation; }
	inline glm::vec3* GetScale(){ return &scale; }

	inline void SetPosition(glm::vec3& position){ this->position = position; }
	inline void SetRotation(glm::vec3& rotation){ this->rotation = rotation; }
	inline void SetScale(glm::vec3& scale){ this->scale = scale; }

private:

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

};